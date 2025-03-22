use crate::{err_fmt, Res};
use std::{
    collections::HashMap,
    mem::transmute,
    ops::{Index, IndexMut},
};

macro_rules! push {
    ($v:expr => [$($x:expr),*]) => {{
        let i = $v.len();
        $($v.push($x);)*
        i
    }};
}

macro_rules! push_each {
    ($v:expr => $x:expr) => {{
        let i = $v.len();
        $x.iter().for_each(|x| $v.push(*x));
        (i, $v.len())
    }};
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub struct Obj(u64);

impl Obj {
    pub unsafe fn from_f64(x: f64) -> Self {
        Self(transmute(x))
    }

    pub unsafe fn to_f64(&self) -> f64 {
        transmute(self.0)
    }
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum Type {
    U64,
    I64,
    F64,
    Str,
}

#[derive(Copy, Clone, Debug, PartialEq)]
pub struct Row(pub usize, pub usize);

#[derive(Clone, Debug, PartialEq)]
pub struct Table {
    head: Vec<Type>,
    body: Vec<usize>,
}

impl Table {
    pub fn iter<'a>(&'a self, db: &'a DB) -> RowIter<'a> {
        RowIter {
            i: 0,
            len: self.head.len(),
            db,
            body: self.body.iter(),
        }
    }
}

pub struct RowIter<'a> {
    pub i: usize,
    pub len: usize,
    pub db: &'a DB,
    pub body: std::slice::Iter<'a, usize>,
}

impl<'a> Iterator for RowIter<'a> {
    type Item = &'a [Obj];

    fn next(&mut self) -> Option<Self::Item> {
        if let Some(Row(i, e)) = self.body.next().map(|x| self.db.rows[*x]) {
            Some(&self.db.objs[i..e])
        } else {
            None
        }
    }
}

#[derive(Clone, Debug, PartialEq)]
pub struct Map<T>(pub usize, pub HashMap<usize, T>);

impl<T> Map<T> {
    pub fn new() -> Self {
        Self(0, HashMap::new())
    }

    pub fn push(&mut self, x: T) {
        self.1.insert(self.0, x);
        self.0 += 1;
    }

    #[inline]
    pub fn len(&self) -> usize {
        self.1.len()
    }

    #[inline]
    pub fn iter(&self) -> std::collections::hash_map::Iter<'_, usize, T> {
        self.1.iter()
    }
}

impl<T> Index<usize> for Map<T> {
    type Output = T;

    fn index(&self, x: usize) -> &Self::Output {
        &self.1[&x]
    }
}

impl<T> IndexMut<usize> for Map<T> {
    fn index_mut(&mut self, x: usize) -> &mut Self::Output {
        self.1.get_mut(&x).expect("key not found")
    }
}

#[derive(Clone, Debug, PartialEq)]
pub struct DB {
    pub strs: Map<String>,
    pub objs: Vec<Obj>,
    pub rows: Map<Row>,
    pub tables: Map<Table>,
}

impl DB {
    pub fn new() -> Self {
        Self {
            strs: Map::new(),
            objs: Vec::new(),
            rows: Map::new(),
            tables: Map::new(),
        }
    }

    pub fn dump(&self) -> String {
        self.tables
            .iter()
            .map(|(i, x)| {
                format!(
                    "table {i:3}:\n{}\n{}",
                    x.head
                        .iter()
                        .map(|x| format!("{:12} ", format!("{x:?}")))
                        .collect::<String>(),
                    x.iter(self)
                        .map(|x| x
                            .iter()
                            .map(|x| format!("{:12} ", format!("{x:?}")))
                            .collect::<String>())
                        .collect::<Vec<_>>()
                        .join("\n")
                )
            })
            .collect::<Vec<String>>()
            .join("\n")
    }

    pub fn insert_row(&mut self, t: usize, x: &[Obj]) -> Res<usize> {
        let tab = &mut self.tables[t];
        if tab.head.len() != x.len() {
            return err_fmt!(
                "mismatched length in insert_row(): {} != {}",
                tab.head.len(),
                x.len()
            );
        }

        let (i, e) = push_each!(self.objs => x);
        let r = push!(self.rows => [Row(i, e)]);

        tab.body.push(r);
        Ok(r)
    }

    pub fn new_table(&mut self, head: Vec<Type>) -> usize {
        push!(self.tables => [Table {
            head,
            body: Vec::new(),
        }])
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn construct() {
        let mut db = DB::new();
        let t = db.new_table(vec![Type::I64, Type::I64]);
        db.insert_row(t, &[Obj(0), Obj(1)]).unwrap();
        db.insert_row(t, &[Obj(2), Obj(3)]).unwrap();
        println!("{db:#?}\n{}", db.dump());
    }
}

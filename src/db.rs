use crate::{Res, err_fmt};
use std::mem::transmute;

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
pub struct Row<'a>(pub &'a [Obj]);

#[derive(Clone, Debug, PartialEq)]
pub struct Table<'a> {
    head: Vec<Type>,
    body: Vec<&'a Row<'a>>,
}

#[derive(Clone, Debug, PartialEq)]
pub struct DB<'a> {
    pub strs: Vec<String>,
    pub objs: Vec<Obj>,
    pub rows: Vec<Row<'a>>,
    pub tables: Vec<Table<'a>>,
}

impl<'a> DB<'a> {
    pub fn new() -> Self {
        Self {
            strs: Vec::new(),
            objs: Vec::new(),
            rows: Vec::new(),
            tables: Vec::new(),
        }
    }

    pub fn dump(&'a self) -> String {
        self.tables.iter()
            .enumerate()
            .map(|(i, x)| format!(
                    "table {i:3}:\n{}\n{}",
                    x.head.iter().map(|x| format!("{x:?}\n")).collect::<String>(),
                    x.body.iter().map(|x| format!("{x:?}\n")).collect::<String>()
            ))
            .collect::<Vec<String>>()
            .join("\n")
    }

    pub fn insert_row(&'a mut self, t: usize, x: &[Obj]) -> Res<usize> {
        let t = &mut self.tables[t];
        if t.head.len() != x.len() {
            return err_fmt!("mismatched length in insert_row(): {} != {}", t.head.len(), x.len());
        }

        let (i, e) = push_each!(self.objs => x);
        let r = push!(self.rows => [Row(&self.objs[i..e])]);

        t.body.push(&self.rows[r]);
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
        let r = db.insert_row(t, &[Obj(0), Obj(1)]).unwrap();
    }
}

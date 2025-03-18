pub mod db;

#[macro_export]
macro_rules! err_fmt {
    ($($t:tt)*) => {{
        Err(format!($($t)*))
    }};
}

pub type Res<T> = Result<T, String>;

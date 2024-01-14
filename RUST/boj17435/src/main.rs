use std::io::{stdin, Read};

const logbound : usize = 19;
fn func<R: BufRead, W: Write>(io: &mut IO<R, W>) -> Option<()> {

    // 1. Input f1
    let m = io.get(0usize)?;
    let mut lca: Vec<Vec<usize>> = vec![vec![0 as usize; logbound]; m+1];
    for _i in 1..(m+1){
        let a = io.get(0usize)?;
        lca[_i as usize][0] = a;
    }

    // 2. build LCA array
    for i in 1..logbound{
        for j in 1..(m+1){
            lca[j][i] = lca[lca[j][i-1]][i-1];
        }
    }

    // 3. Processing Query
    let q = io.get(0usize)?;
    for _q in 0..q{
        let [n, x] = io.get([0usize; 2])?;
        let mut n = n;
        let mut x = x;
        let mut unit = 0;
        while n > 0 {
            if n % 2 == 1{
                x = lca[x as usize][unit];
            }
            n >>= 1;
            unit += 1;
        }
        io.put(x).nl();
    }
    None
}


/// IO template
mod io {
	pub(crate) use std::io::{Write, stdin, stdout, BufWriter, BufRead};
	pub(crate) struct IO<R: BufRead, W: Write> {
		ii: I<R>,
		oo: BufWriter<W>,
	}
	impl<R: BufRead, W: Write> IO<R, W> {
		pub(crate) fn new(r: R, w: W) -> Self {
			Self {
				ii: I::new(r),
				oo: BufWriter::new(w),
			}
		}
		pub(crate) fn get<T: Fill>(&mut self, exemplar: T) -> Option<T> {
			self.ii.get(exemplar)
		}
		pub(crate) fn put<T: Print>(&mut self, t: T) -> &mut Self {
			t.print(&mut self.oo);
			self
		}
		pub(crate) fn nl(&mut self) -> &mut Self {
			self.put("\n")
		}
	}
	pub(crate) trait Print {
		fn print<W: Write>(&self, w: &mut W);
	}
	macro_rules! print_disp {
		($($t:ty),+) => {
			$(impl Print for $t { fn print < W : Write > (& self, w : & mut W) {
			write!(w, "{}", self) .unwrap(); } })+
		};
	}
	print_disp!(usize, i64, String, & str, char);
	pub(crate) struct I<R: BufRead> {
		r: R,
		line: String,
		rem: &'static str,
	}
	impl<R: BufRead> I<R> {
		pub(crate) fn new(r: R) -> Self {
			Self {
				r,
				line: String::new(),
				rem: "",
			}
		}
		pub(crate) fn next_line(&mut self) -> Option<()> {
			self.line.clear();
			(self.r.read_line(&mut self.line).unwrap() > 0)
				.then(|| {
					self
						.rem = unsafe {
						(&self.line[..] as *const str).as_ref().unwrap()
					};
				})
		}
		pub(crate) fn get<T: Fill>(&mut self, exemplar: T) -> Option<T> {
			let mut exemplar = exemplar;
			exemplar.fill_from_input(self)?;
			Some(exemplar)
		}
	}
	pub(crate) trait Fill {
		fn fill_from_input<R: BufRead>(&mut self, i: &mut I<R>) -> Option<()>;
	}
	fn ws(c: char) -> bool {
		c <= ' '
	}
	macro_rules! fill_num {
		($($t:ty),+) => {
			$(impl Fill for $t { fn fill_from_input < R : BufRead > (& mut self, i : &
			mut I < R >) -> Option < () > { i.rem = i.rem.trim_start_matches(ws); while i
			.rem.is_empty() { i.next_line() ?; i.rem = i.rem.trim_start_matches(ws); }
			let tok = i.rem.split(ws).next().unwrap(); i.rem = & i.rem[tok.len()..]; *
			self = tok.parse().ok() ?; Some(()) } })+
		};
	}
	fill_num!(usize, i64, f64);
	impl<T: Fill> Fill for Vec<T> {
		fn fill_from_input<R: BufRead>(&mut self, i: &mut I<R>) -> Option<()> {
			for ii in self.iter_mut() {
				ii.fill_from_input(i)?;
			}
			Some(())
		}
	}
	impl<T: Fill, const N: usize> Fill for [T; N] {
		fn fill_from_input<R: BufRead>(&mut self, i: &mut I<R>) -> Option<()> {
			for ii in self.iter_mut() {
				ii.fill_from_input(i)?;
			}
			Some(())
		}
	}
}
use io::*;
pub fn main() {
	let stdin = stdin().lock();
	let stdout = stdout().lock();
	let mut io = IO::new(stdin, stdout);
	func(&mut io);
}

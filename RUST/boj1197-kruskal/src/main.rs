use std::io::{stdin, Read};
use std::cmp::Ordering;

fn find_root(mut parent: &mut [usize; 10001], a: usize) -> usize{
    if parent[a] == a{
        a
    }else{
        parent[a] = find_root(parent, parent[a]);
        parent[a]
    }
}
fn make_union(mut parent: &mut [usize; 10001], a: usize, b: usize){
    parent[b] = a;
}



fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().flat_map(str::parse::<i32>);

    let v = input.next().unwrap() as usize;
    let e = input.next().unwrap() as usize;

    let mut edges : Vec<(usize, usize, i32)> = vec![];

    // Input
    for _i in 0..e{
        let a = input.next().unwrap() as usize;
        let b = input.next().unwrap() as usize;
        let c = input.next().unwrap();

        edges.push((a, b, c));
    }

    // KRUSKAL
    edges.sort_by(|a, b| a.2.cmp(&b.2));
    let mut parent: [usize; 10001] = [0; 10001];
    let mut ANS = 0;

    for _i in 1..(v+1){
        parent[_i] = _i;
    }

    for edge in &edges{
        let a_root = find_root(&mut parent, edge.0);
        let b_root = find_root(&mut parent, edge.1);

        if a_root != b_root {
            make_union(&mut parent, a_root, b_root);
            ANS += edge.2;
        }
    }
    println!("{ANS}");
}

use std::io::{stdin, Read};

fn dfs(i: usize, graph: &Vec<Vec<usize>>, parent: &mut[usize;1001], visited: &mut[bool;1001]) -> bool{
    let graph_iter = graph[i].iter();
    if visited[i]{
        return false;
    }
    visited[i] = true;

    for _j in graph_iter{
        if parent[*_j] == 0 || dfs(parent[*_j], graph, parent, visited){
            parent[*_j] = i;
            return true;
        }
    }
    false
}

fn main() {
    // 1. Input graph
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().flat_map(str::parse::<usize>);

    let N = input.next().unwrap();
    let M = input.next().unwrap();
    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); N+1];
    let mut parent: [usize; 1001] = [0; 1001];

    for _i in 1..(N+1){
        let w = input.next().unwrap();
        for _j in 0..w{
            let a = input.next().unwrap();
            graph[_i].push(a);
        }
    }

    // 2. do DFS sequentially
    let mut ANS = 0;
    for _i in 1..(N+1){
        let mut visited: [bool; 1001] = [false; 1001];
        if dfs(_i, &graph, &mut parent, &mut visited){
            ANS += 1;
        }
    }
    println!("{ANS}");
}
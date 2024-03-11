use std::io::{stdin, Read};

fn dfs(i: usize, graph: &Vec<Vec<usize>>, parent: &mut [usize; 501], visited: &mut [bool; 501]) -> usize{
    for next in graph[i].iter(){
        if visited[*next] {
            continue;
        }
        visited[*next] = true;
        if parent[*next] == 0 || dfs(parent[*next], graph, parent, visited) == 1{
            parent[*next] = i;
            return 1;
        }
    }
    return 0;
}
fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().flat_map(str::parse::<usize>);

    let n = input.next().unwrap();
    let k = input.next().unwrap();

    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); n + 1];
    for _k in 1..(k + 1){
        let a = input.next().unwrap();
        let b = input.next().unwrap();
        graph[a].push(b);
    }
    
    let mut ANS = 0;
    let mut parent: [usize; 501] = [0; 501];
    for _n in 1..(n + 1){
        let mut visited: [bool; 501] = [false; 501];
        ANS += dfs(_n, &graph, &mut parent, &mut visited);
    }
    println!("{ANS}");
}

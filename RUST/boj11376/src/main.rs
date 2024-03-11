use std::io::{stdin, Read};
const PARENT_DEFAULT: usize = 2001;

fn dfs(i: usize, graph: &Vec<Vec<usize>>, mut parent: &mut [usize; 2000], mut visited: &mut [bool; 2000]) -> usize{
    for next in graph[i].iter(){
        if visited[*next] {
            continue;
        }
        visited[*next] = true;
        if parent[*next] == PARENT_DEFAULT || dfs(parent[*next], graph, parent, visited) == 1{
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

    let N = input.next().unwrap();
    let M = input.next().unwrap();

    let mut graph: Vec<Vec<usize>> = vec![Vec::<usize>::new(); 2 * N];
    for _n in 0..N {
        let k = input.next().unwrap();

        for _k in 0..k{
            let a = input.next().unwrap();
            graph[_n * 2].push(a);
            graph[_n * 2 + 1].push(a);
        }
    }

    let mut parent: [usize; 2000] = [PARENT_DEFAULT; 2000];
    let mut ANS = 0;
    for i in 0..(2 * N) {
        let mut visited: [bool; 2000] = [false; 2000];
        ANS += dfs(i, &graph, &mut parent, &mut visited);
    }
    println!("{ANS}");
}

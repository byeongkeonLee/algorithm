use std::io::{stdin, Read};
const PARENT_DEFAULT: usize = 99;
fn eratosthenes(prime: &mut [bool; 2001]) -> (){
    prime[1] = false;
    prime[2] = true;
    for i in 2..2001 {
        if prime[i] {
            let mut j = i * 2;
            while j < 2001{
                prime[j] = false;
                j += i;
            }
        }
    }
}

fn dfs(i: usize, graph: &Vec<Vec<usize>>, parent: &mut [usize; 26], visited: &mut [bool; 26]) -> usize{
    for next in graph[i].iter(){
        if visited[*next]{
            continue;
        }
        visited[*next] = true;
        if parent[*next] == PARENT_DEFAULT || dfs(parent[*next], graph, parent, visited) == 1{
            parent[*next] = i;
            return 1;
        }
    }
    0
}

fn main() {

    // 1. Get Inputs from stdin
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().flat_map(str::parse::<usize>);

    let N = input.next().unwrap();
    let mut flag : usize = 0;
    let mut numbers: [[usize; 50]; 2] = [[0; 50]; 2];
    let mut flag_cnt: usize = 0;
    let mut flag_xor_cnt: usize = 0;

    for _n in 0..N {
        let input_num = input.next().unwrap();
        if _n == 0{
            flag = input_num % 2;
        }
        numbers[input_num % 2][if input_num % 2 == flag {flag_cnt} else {flag_xor_cnt}] = input_num;
        if input_num % 2 == flag {flag_cnt += 1} else {flag_xor_cnt += 1};
    }

    // 1-1. shortcut
    if flag_cnt != flag_xor_cnt {
        println!("-1");
        return;
    }

    // 2. Do Sieve of Eratosthenes
    let mut prime: [bool; 2001] = [true; 2001];
    eratosthenes(&mut prime);

    // 3. Create Graph
    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); N/2];
    for _i in 0..flag_cnt{
        for _j in 0..flag_xor_cnt{
            if prime[numbers[flag][_i] + numbers[flag^1][_j]] {
                graph[_i].push(_j);
            }
        }
    }

    // 4. Do Bipartite matching
    let mut ANS: Vec<usize> = Vec::new();
    for _i in graph[0].iter() {
        let mut parent: [usize; 26] = [PARENT_DEFAULT; 26];
        parent[*_i] = 0;
        let mut result: usize = 1;
        
        for _j in 1..flag_xor_cnt{
            let mut visited: [bool; 26] = [false; 26];
            visited[*_i] = true;
            result += dfs(_j, &graph, &mut parent, &mut visited);
        }
        if result == N/2 {
            ANS.push(numbers[flag^1][*_i]);
        }
    }

    //5. Sorting
    if ANS.len() == 0 {
        print!("-1");
        return;
    }
    ANS.sort();
    for _a in ANS.iter(){
        print!("{} ", *_a);
    }
}

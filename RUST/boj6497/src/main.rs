use std::io::{stdin, Read};
use std::cmp::Ordering;
use std::collections::BinaryHeap;

#[derive(Clone, Copy, Eq, PartialEq)]
struct Node{
    node: usize,
    weight: i32,
}

impl Ord for Node{
    fn cmp(&self, other: &Self) -> Ordering{
        other.weight.cmp(&self.weight)
    }
}
impl PartialOrd for Node{
    fn partial_cmp(&self, other:&Self) -> Option<Ordering>{
        Some(self.cmp(other))
    }
}

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().flat_map(str::parse::<i32>);

    loop{
        let m = input.next().unwrap() as usize;
        let n = input.next().unwrap() as usize;
        
        let mut graph : Vec<Vec<Node>> = vec![Vec::new(); m];
        if m == 0 && n == 0 {
            break;
        }

        let mut TOTAL = 0;
        for _i in 0..n{
            let a = input.next().unwrap() as usize;
            let b = input.next().unwrap() as usize;
            let c = input.next().unwrap();

            graph[a].push(Node{node: b, weight: c});
            graph[b].push(Node{node: a, weight: c});
            TOTAL += c;
        }
        
        let mut heap: BinaryHeap<Node> = BinaryHeap::new();
        let mut visited: [bool; 200000] = [false; 200000];
        let mut ANS = 0;

        heap.push(Node{node:0, weight:0});
        while let Some(Node {node, weight}) = heap.pop(){
            if visited[node]{
                continue;
            }
            ANS += weight;
            visited[node] = true;
            for next in &graph[node]{
                if !visited[next.node]{
                    heap.push(Node{node: next.node, weight: next.weight});
                }
            }
        }
        let result = TOTAL-ANS;
        println!{"{result}"};
    }
}

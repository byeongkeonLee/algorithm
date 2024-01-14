use std::io::{stdin, Read};

const DR: [i32; 6] = [-1, -1, 0, 1, 1, 0];
const DC: [i32; 6] = [-1, 1, 1, 1, -1, -1];

fn dfs(i: usize, graph: &Vec<Vec<usize>>, visited: &mut Vec<bool>, parent: &mut Vec<i32>) -> usize{
    for _r in graph[i].iter(){
        if visited[*_r] == true{
            continue;
        }
        visited[*_r] = true;
        if parent[*_r] == -1 || dfs(parent[*_r] as usize, graph, visited, parent) == 1{
            parent[*_r] = i as i32;
            return 1;
        }
    }
    return 0;
}
fn main(){
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace();

    let tc = input.next().unwrap().parse::<usize>().unwrap();
    for _tc in 0..tc{
        let n = input.next().unwrap().parse::<usize>().unwrap();
        let m = input.next().unwrap().parse::<usize>().unwrap();
        let mut arr: Vec<String> = Vec::<String>::new();

        for _l in 0..n{
            arr.push(input.next().unwrap().to_string());
        }

        let mut graph = vec![Vec::<usize>::new(); m * n];
        let mut list: Vec<usize> = Vec::<usize>::new();
        let mut node_count = 0;
        for _n in 0..n{
            for _m in 0..m{
                if arr[_n].as_bytes()[_m] != b'.'{
                    continue;
                }
                node_count += 1;
                let cindex = _n * m + _m;
                if _m % 2 == 0{
                    list.push(cindex);
                }else{
                    continue;
                }
                for _dir in 0..6{
                    let ndr = _n as i32 + DR[_dir];
                    let ndc = _m as i32 + DC[_dir];
                    if ndr < 0 || ndr >= n as i32 || ndc < 0 || ndc >= m as i32{
                        continue;
                    }

                    let ndr = ndr as usize;
                    let ndc = ndc as usize;
                    let nindex = ndr * m + ndc;
                    if arr[ndr].as_bytes()[ndc] == b'.'{
                        graph[cindex].push(nindex);
                    }
                }
            }
        }

        let mut ANS = 0;
        let mut parent = vec![-1; m * n];
        //println!("{:?}", list);
        for l in list{
            let mut visited = vec![false; m * n];
            ANS += dfs(l, &graph, &mut visited, &mut parent);
        }
        //println!("{:?}", graph);
        println!("{}", node_count - ANS);
    }
}
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <cmath>

#define INF 1e9

using namespace std;

vector<vector<int>> capacidade, grafo;

// Acha um caminho possivel
int bfs(int s, int t, vector<int>& pai) {
    fill(pai.begin(), pai.end(), -1);

    pai[s] = -2;
    queue<pair<int,int>> q;

    q.push({s,INF}); 

    while(!q.empty()) {
        int atual = q.front().first;
        int fluxo = q.front().second;
        q.pop();


        for (int viz: grafo[atual]) {
            if (pai[viz] == -1 && capacidade[atual][viz]) {
                pai[viz] = atual;
                int novo_fluxo = min(fluxo, capacidade[atual][viz]);
                if (viz == t) 
                    return novo_fluxo;
                q.push({viz, novo_fluxo});
            }
        }
    }
    return 0;
}

// Acha o fluxo máximo
int fluxo_maximo(int s, int t, int n) {
    int fluxo = 0, novo_fluxo;

    vector<int> pai(n);
    while(novo_fluxo = bfs(s, t, pai)) {
        fluxo = novo_fluxo;
        int atual = t;
        while(atual != s) {
            int anterior = pai[atual];
            capacidade[anterior][atual] -= novo_fluxo;
            capacidade[atual][anterior] += novo_fluxo;
            atual = anterior;
        }
    }
    return fluxo;
}


int main() {
    capacidade.assign(3, vector<int>(3,0));
    grafo.assign(3, vector<int>());

    int n;
    cin >> n;
   
    // seta o grafo e a matriz de capacidade como: S ->(n/2 arredondado pra cima) no ->(n/2 arredondado pra baixo) T
    capacidade[0][1] = n - (n/2);
    grafo[0].push_back(1);
    grafo[1].push_back(0);
    capacidade[1][2] = n/2;
    grafo[1].push_back(2);
    grafo[2].push_back(1);

    // calcula o fluxo e atualiza a matriz de capacidade
    fluxo_maximo(0, 2, 3);
    
    // converte a capacidade restante de S para no na letra correta.
    cout << (char) ('B' - capacidade[0][1]);

    return 0;
}
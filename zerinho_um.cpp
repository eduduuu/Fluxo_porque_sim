#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <cmath>

#define INF 1e9

using namespace std;

vector<vector<int>> capacidade, grafo;

// Acha um caminho possível
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
    capacidade.assign(5, vector<int>(5,0));
    grafo.assign(5, vector<int>());

    // Vetor com os números (0 ou 1) para cada jogador
    vector<int> numeros_escolhidos;
    int qntd_1 = 0;

    for (int i = 0; i < 3; i++) {
        numeros_escolhidos.push_back(0);
        cin >> numeros_escolhidos[i];
        if(numeros_escolhidos[i]) qntd_1++;
    }

    // inverte se necessário os valores, para que se tenha no máximo um valor 1
    if (qntd_1 > 1)
        for (int i = 0; i < 3; i++) {
            if (numeros_escolhidos[i])
                numeros_escolhidos[i] = 0;
            else
                numeros_escolhidos[i] = 1;
        }

    // seta o grafo e a matriz de capacidade com arestas entre S e cada jogador e entre cada jogador e T
    // como o número escolhido (Invertido ou não) 
    for (int i = 0; i < 3; i++) {
        capacidade[0][i+1] = numeros_escolhidos[i];
        grafo[0].push_back(i+1);
        grafo[i+1].push_back(0);
        capacidade[i+1][4] = numeros_escolhidos[i];
        grafo[4].push_back(i+1);
        grafo[i+1].push_back(4);
    }

    // calcula o fluxo e atualiza a matriz de capacidade
    // se o fluxo for 0 Não há ganhador
    if (!fluxo_maximo(0, 4, 5)) {
        cout << "*";
        return 0;
    }
    
    // converte a posição do único jogador com capacidade na aresta vinda de S para a letra correta
    for (int i = 1; i < 4; i++) {
        if (capacidade[i][0])
            cout << (char) ('A' + i - 1);
    }


    return 0;
}

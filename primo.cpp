#include <iostream>
#include <bits/stdc++.h>

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

// Acha o fluxo maximo
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
    int n; // numero limite
    cin >> n;
    capacidade.assign(n+2, vector<int>(n+2,0));
    grafo.assign(n+2, vector<int>());


    // seta o grafo e as capacidade da mesma forma do algoritmo pra checar se um numero é par
    for (int i = 3; i <= n; i++) {
        capacidade[0][i] = i - i/2;
        grafo[0].push_back(i);
        grafo[i].push_back(0);
        capacidade[i][n+1] = i/2;
        grafo[n+1].push_back(i);
        grafo[i].push_back(n+1);
    }

    // 2 é obviamente primo
    cout << "2 ";

    // ind é o valor que estamos comparando atualmente
    int ind = 3;
    while (ind <= n) {
        // atualiza a matriz de capacidade. se fonte -> no tiver valor 0. no é divisivel pelo indice
        fluxo_maximo(0, n+1, n+2);
        // escolhe o próximo indice como algum número que não tem divisor
        while(!capacidade[0][ind]) {
            ind++;
        }
        // esse número é primo. Ele é "excluido" da matriz de capacidade
        if (ind <= n) cout << ind << " ";
        capacidade[0][ind] = 0;

        // atualiza a matriz de capacidade para checar a divisibilidade pelo novo indice
        for (int i = ind+1; i <= n; i++) {
            // se não for divisível pelo anterior
            if (capacidade[0][i]){
                // seta assim se for divisível. (Meio que já dava pra setar como 0, mas aí perderia a graça de usar fluxo)
                if((i/ind)*ind == i) {
                    capacidade[0][i] = ind;
                    capacidade[i][n+1] = ind; 
                }
                // se não, seta desse outra forma aqui
                else {
                    capacidade[0][i] = max(i-(i/ind)*ind, i/ind);
                    capacidade[i][n+1] = min(i-(i/ind)*ind, i/ind); 
                }
            }
        }

    }

    return 0;
}
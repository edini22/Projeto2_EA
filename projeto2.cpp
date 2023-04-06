#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int task;
int N; // N empresas que ele esta a pensar em adicionar ao seu portfolio
int D; // coletou os valores diarios das acoes ao longo de D dias
int K; // nunca ter mais do que K acoes de cada empresa
int R; // taxa fixa

/**
 * John nunca pode ter mais do que K acoes de cada empresa
 * Em cada dia, John pode realizar no maximo uma transação(comprar ou vender quantas acoes quiser dessa empresa).
 * A bolsa que John usa/cobra uma taxa fixa R para cada acao(ex: se comprar 2 acoes em uma transacao sera 2 * R),
    nao havendo para a venda destas
 */

/** Tarefas
 * Tarefa 1 : imprimir o melhor lucro que John poderia ter com a negociacao de acoes de cada empresa.
 * Tarefa 2 : para cada empresa, imprimir o melhor lucro e imprimir a informacao de quantas acoes para
   comprar ou vender todos os dias para obter o melhor lucro(atribuir numeros positivos para compras e negativos para vendas)
 * Tarefa 3 : imprimir o melhor lucro e quantos esquemas de negociacao diferentes davam esse mesmo lucro (lucro numero)
    (a+b) mod  m = ((a mod  m)+(b mod  m)) mod  m para o numero de esquemas
 */

vector<vector<int>> V;     // vector que em cada linha representa uma empresa e cada coluna representa um dia
long profit;               // usado para imprimir o lucro total no final
vector<vector<long>> dp;   // guardar a info se naquele dia comprou ou vendeu e qual o profit desse caminho
vector<long> history;      // usado para guardar o historico de compras/vendas ao longo dos dias
vector<long> history_copy; // usado para duplicar o historico no caso de haver mais alguma possibilidade
long long possibilidades;        // guardar quantas possibilidades de compras/vendas dariam o lucro maximo

int num_a;
long max_profit;

void writeVector() {
    int num;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < D; j++) {
            cin >> num;
            V[i][j] = num;
        }
    }
}

// DP
long maxProfit(int company, int day, int buy) {

    if (day == D) {
        return 0;
    }

    if (dp[day][buy] != -1) {
        return dp[day][buy];
    }

    long prof = 0;

    if (buy) {
        prof = max(-V[company][day] * K - R * K + maxProfit(company, day + 1, 0),
                   0 + maxProfit(company, day + 1, 1));
    } else {
        prof = max(V[company][day] * K + maxProfit(company, day + 1, 1),
                   0 + maxProfit(company, day + 1, 0));
    }

    return dp[day][buy] = prof;
}

// Bottom Up
long maxProfit2(int company) {
    vector<long> next = vector<long>(2, 0);
    vector<long> cur = vector<long>(2, 0);

    next[0] = next[1] = 0;
    for (int day = D - 1; day >= 0; day--) {
        long prof = 0;
        for (int buy = 0; buy <= 1; buy++) {
            prof = 0;
            if (buy) {
                prof = max(-V[company][day] * K - R * K + next[0],
                           0 + next[1]);
            } else {
                prof = max(V[company][day] * K + next[1],
                           0 + next[0]);
            }
            cur[buy] = prof;
        }
        next = cur;
    }
    return next[1];
}

void task1() {
    for (int i = 0; i < N; i++) {
        profit = maxProfit2(i);
        cout << profit << endl;
    }
}

void bestSequence(int company) {
    int buy = 1;
    for (int day = 0; day < D; day++) {

        if (day != D - 1) {
            long prof = dp[day][buy];
            if (prof == -V[company][day] * K - R * K + maxProfit(company, day + 1, 0)) {
                history[day] = K;
                buy = 0;
            } else if (prof == V[company][day] * K + maxProfit(company, day + 1, 1)) {
                history[day] = -K;
                buy = 1;
            } else {
                history[day] = 0;
            }
        } else {

            // tratar do ultimo elemento
            if (buy) {
                history[day] = 0; // vender todas as ações no último dia
            } else {
                history[day] = -K; // não há ações para vender no último dia
            }
        }
    }
}

void task2() {
    for (int i = 0; i < N; i++) {
        history = vector<long>(D, 0);

        // dp
        dp = vector<vector<long>>(D, vector<long>(2, -1));
        profit = maxProfit(i, 0, 1);

        // bottom up
        // profit = maxProfit2(i);
        cout << profit << endl;

        // bestProfit(i);
        bestSequence(i);

        for (int j = 0; j < D; j++) {
            cout << history[j] << " ";
        }

        cout << endl;
    }
}

long long numCombinations(int K, int D) {
    vector<vector<long long>> dpc(D + 1, vector<long long>(K + 1, 0));

    // Caso base: 0 dias e 0 ações compradas
    dpc[0][0] = 1;

    for (int day = 1; day <= D; day++) {
        for (int numShares = 0; numShares <= K; numShares++) {
            // Não compra nenhuma ação no dia atual
            dpc[day][numShares] = dpc[day - 1][numShares];

            // Compra j ações no dia atual (j varia de 1 até o máximo possível)
            for (int j = 1; j <= min(numShares, K); j++) {
                dpc[day][numShares] += dpc[day - 1][numShares - j];
            }
        }
    }

    return dpc[D][K];
}

void maxcombinations(int company) {
    int buy = 1;
    for (int day = 0; day < D; day++) {

        if (day != D - 1) {
            long prof = dp[day][buy];
            if (prof == -V[company][day] * K - R * K + maxProfit(company, day + 1, 0)) {
                int count = 0;
                for (int i = day; i < D - 1; i++) { // ficar o ultimo para vender pelo menos !
                    // ver quantas permutacoes da para fazer com esses num iguais!!
                    if (V[company][day] == V[company][i]) {
                        count++;
                    }

                    else
                        break;
                }
                if (count > 1) {
                    possibilidades *= numCombinations(K, count);
                    // cout << "k: " << K << "count: " << count << "possibilidades: " <<possibilidades << endl;
                }
                buy = 0;
            } else if (prof == V[company][day] * K + maxProfit(company, day + 1, 1)) {
                int count = 0;
                for (int i = day; i < D; i++) { // ficar o ultimo para vender pelo menos !
                    // ver quantas permutacoes da para fazer com esses num iguais!!
                    if (V[company][day] == V[company][i]) {
                        count++;
                    }

                    else
                        break;
                }
                if (count > 1) {
                    possibilidades *= numCombinations(K, count);
                    // cout << "k: " << K << "count: " << count << "possibilidades: " <<possibilidades << endl;
                }
                buy = 1;
            } 
        } else {

            // tratar do ultimo elemento
            // if (buy) {
            //     history[day] = 0; // vender todas as ações no último dia
            // } else {
            //     history[day] = -K; // não há ações para vender no último dia
            // }
        }
    }
}

void task3() {
    for (int i = 0; i < N; i++) {
        num_a = 0;
        // dp
        dp = vector<vector<long>>(D, vector<long>(2, -1));
        possibilidades = 1;
        max_profit = maxProfit(i, 0, 1);
        maxcombinations(i);
        cout << max_profit << " " << possibilidades << endl;
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    cin >> task;

    cin >> N >> D >> K >> R;

    V = vector<vector<int>>(N, (vector<int>(D, 0)));
    profit = 0;

    writeVector();

    switch (task) {
    case 1:
        task1();

        break;
    case 2:
        task2();

        break;
    case 3:
        task3();

        break;
    default:
        break;
    }

    return 0;
}
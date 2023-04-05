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

vector<vector<int>> V;    // vector que em cada linha representa uma empresa e cada coluna representa um dia
int profit;               // usado para imprimir o lucro total no final
vector<vector<int>> dp;   // guardar a info se naquele dia comprou ou vendeu e qual o profit desse caminho
vector<int> history;      // usado para guardar o historico de compras/vendas ao longo dos dias
vector<int> history_copy; // usado para duplicar o historico no caso de haver mais alguma possibilidade
int possibilidades;       // guardar quantas possibilidades de compras/vendas dariam o lucro maximo

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
int maxProfit(int company, int day, int buy) {

    if (day == D) {
        return 0;
    }

    if (dp[day][buy] != -1) {
        return dp[day][buy];
    }

    int prof = 0;

    if (buy) {
        prof = max(-V[company][day] * K - R * K + maxProfit(company, day + 1, 0),
                   0 + maxProfit(company, day + 1, 1));

        // if (prof == -V[company][day] * K - R * K + maxProfit(company, day + 1, 0)) {
        //     cout << "Comprei dia" << day + 1 << " DP" << dp[day][buy] << endl;
        // } else {
        //     cout << "Mantive dia" << day + 1 << " DP" << dp[day][buy] << endl;
        // }
    } else {
        prof = max(V[company][day] * K + maxProfit(company, day + 1, 1),
                   0 + maxProfit(company, day + 1, 0));

        // if (prof == V[company][day] * K + maxProfit(company, day + 1, 1)) {
        //     cout << "Vendi dia" << day + 1 << " DP" << dp[day][buy] << endl;
        // } else {
        //     cout << "Mantive dia" << day + 1 << " DP" << dp[day][buy] << endl;
        // }
        // cout << endl;
    }

    return dp[day][buy] = prof;
}

// Bottom Up
int maxProfit2(int company) {
    vector<int> next = vector<int>(2, 0);
    vector<int> cur = vector<int>(2, 0);

    next[0] = next[1] = 0;
    for (int day = D - 1; day >= 0; day--) {
        int prof = 0;
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
            int prof = dp[day][buy];
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
        history = vector<int>(D, 0);

        // dp
        dp = vector<vector<int>>(D, vector<int>(2, -1));
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

void task3() {
    for (int i = 0; i < N; i++) {
        dp = vector<vector<int>>(D, vector<int>(2, -1));
        history = vector<int>(D, 0);
        history_copy = vector<int>(D, 0);
        possibilidades = 0;
        profit = maxProfit(i, 0, 1);

        cout << profit << " " << possibilidades << endl;
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
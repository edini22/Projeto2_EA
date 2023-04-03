# Recursao

```
D -> num de dias
Function f(day, buy):
    if day = D:
        return 0

    if buy:
        profit = max(-prices[day] + f(day+1, 0), // comprar neste dia
                        0         + f(day+1, 1)) // vender neste dia 
    else:
        profit = max(prices[day] + f(day+1, 0), 
                        0        + f(day+1, 0)) 

    return profit
```

# DP

```
D -> num de dias
Function f(day, buy):
    // caso base
    if day = D:
        return 0

    // dp
    if dp[day][buy] != -1:
        return dp[day][buy]

    //comprou se no dia anterior
    if buy:
        profit = max(-prices[day] + f(day+1, 0), // comprar neste dia
                        0         + f(day+1, 1)) // vender neste dia 
        dp[day][buy] = profit
    
    // nao se comprou no dia anterior
    else:
        profit = max(prices[day] + f(day+1, 1), 
                        0        + f(day+1, 0)) 
        dp[day][buy] = profit

    return profit
```

# Bottom up
Nao e necessario guardar o array dp inteiro, mas sim a ultima iteracao compra/venda, isto e, se estamos no dia 3, apenas precisamos do dia 4 (comprar ou vender)

```
dp = vector(D, vector(2,0)) 
dp[D][0] = dp[D][1] = 0



Function BU(day, buy):

    vector next = (2,0);
    vector cur = (2,0);
    next[0] = next[1] = 0
    for day=D-1 to 0:
        for buy=0 to 1:
            profit = 0  
            if buy:
                profit = max(-prices[day] + next[0], // comprar neste dia
                                0         + next[1]) // vender neste dia 
                
            
            // nao se comprou no dia anterior
            else:
                profit = max(prices[day] +  next[1], 
                                0        +  next[0]) 
            cur[buy] = profit
        next = cur;
    return next[1] 


```
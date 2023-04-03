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

```
dp[D][0] = dp[D][1] = 0

Function BU:
    for day=D to 0:
        for buy=0 to 1:
            profit = 0  
            if buy:
                profit = max(-prices[day] + dp[day+1][0], // comprar neste dia
                                0         + dp[day+1][1]) // vender neste dia 
                dp[day][buy] = profit
            
            // nao se comprou no dia anterior
            else:
                profit = max(prices[day] +  dp[day+1][1], 
                                0        +  dp[day+1][0]) 
                dp[day][buy] = profit

    return dp[0][1]


```
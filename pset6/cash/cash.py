
while True:
    dinheiro = float(input("Digite o troco: "))
    if dinheiro > 0:
        break
    else:
        print("Valor inválido, tente novamente")

centavos = dinheiro * 100
moedas = 0

moedas += centavos // 25
centavos %= 25

moedas += centavos // 10
centavos %= 10

moedas += centavos // 5
centavos %= 5

moedas += centavos // 1
centavos %= 1

print(f"moedas necessárias para o troco: {moedas:.0f}")

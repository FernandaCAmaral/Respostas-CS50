while True:
    altura = int(input("Escolha a altura da pirâmide (1 a 8): "))
    if altura > 0 and altura < 9:
        break

for i in range (0, altura, 1):
    for j in range (0, altura, 1):
        if i + j >= altura - 1:
            print("#", end="")
        else:
            print(" ", end="")

    print("  ", end="")

    for j in range(0, altura, 1):
        if i + j >= altura - 1:
            print("#", end="")

    print()

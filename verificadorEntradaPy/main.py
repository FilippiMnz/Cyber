def detectar_invasao(registros):
    usuario_atual = None
    tentativas_consecutivas = 0
    invasor_detectado = None

    for registro in registros:
        id_usuario, status = registro.split(":")
        
        if id_usuario == usuario_atual:
            if status == "falha":
                tentativas_consecutivas += 1
            else:
                tentativas_consecutivas = 0
        else:
            if tentativas_consecutivas > 3:
                invasor_detectado = usuario_atual
            usuario_atual = id_usuario
            tentativas_consecutivas = 1 if status == "falha" else 0

    if tentativas_consecutivas > 3:
        invasor_detectado = usuario_atual

    return invasor_detectado if invasor_detectado else "Nenhum invasor detectado"

def main():
    entrada = input()
    
    registros = [registro.strip() for registro in entrada.split(",")]

    resultado = detectar_invasao(registros)

    print(resultado)

if __name__ == "__main__":
    main()


def verificar_phishing(mensagem):
    palavras_suspeitas = ["ganhe", "prêmio", "urgente", "desconto", "click", "promoção"]
    
    for palavra in palavras_suspeitas:
        if palavra.lower() in mensagem.lower():
            return "Phishing"
    
    return "Seguro"

email_usuario = input()

email_usuario = email_usuario.strip()

resultado = verificar_phishing(email_usuario)

print(f"Classificação: {resultado}")


const BarraProgresso = document.querySelector(".progress-circle");
const TextoProgresso = document.querySelector(".progress-value"); 



let contadorAtual = 0;
let valorFinal = 85;
let velocidade = 20;

//Função de teste

let loopAnimacao = setInterval(() => {
    contadorAtual++;

    TextoProgresso.textContent = `${contadorAtual}%`;

    let Graus = contadorAtual * 1.8;

    BarraProgresso.style.setProperty("--progress", `${Graus}deg`)

    if (contadorAtual === valorFinal){
        clearInterval(loopAnimacao)
    }


}, velocidade)
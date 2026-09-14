/*
SCRIPT PRINCIPAL DO PROJETO
ESCOPO DO PROJETO:
TODO:

-Medidor de umidade baseado em barra de progresso animada. (% do progresso x 1.8)
-pop up ao entrar na página pedindo uma senha hardcoded no ESP que será dada aos apresentadores, a senha é enviada para o ESP, se for validada, o pop up fecha
e a senha é salva no navegador (possíveis cookies), assim liberando os controles para o apresentador
-Pegar os elementos a serem modificados (Umidade, Regador (on/off), Estufa (On,off) e temperatura) com FETCH, e dar display no HTML.
-Quando a senha registrada é correta os botôes são liberados, e juntamente aos comandos a senha é enviada para validação no ESP

*/












//Definições da Umidade
const Umidade_Progress = document.querySelector(".progress-circle-umidade")
const Umidade_Progress_Text = document.querySelector(".progress-value-umidade")
let Umidade_Valor_Atual = 0
let Umidade_Animacao;

function UpdateUmidade(NewValue) {

    let Velocidade = 20
    clearInterval(Umidade_Animacao)
    
    Umidade_Animacao = setInterval(() => {

        if (Umidade_Valor_Atual < NewValue) 
            {
                Umidade_Valor_Atual++
            }
        else if (Umidade_Valor_Atual > NewValue) {
            Umidade_Valor_Atual--
        }
        else {
            clearInterval(Umidade_Animacao)
            return;
        }

        let CalculoGraus = Umidade_Valor_Atual * 1.8

        Umidade_Progress_Text.textContent =  `${Umidade_Valor_Atual}%`
        Umidade_Progress.style.setProperty("--progress", `${CalculoGraus}deg`)
    

    }, velocidade)

}
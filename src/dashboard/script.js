const API = "https://iot-pet.onrender.com";

async function atualizar(){

  try{

    const resposta =
      await fetch(
        `${API}/ultima-leitura`
      );

    const pet =
      await resposta.json();

    // caso tenha erro
    if(pet.erro){

      document.getElementById("nome")
        .innerText="Pet não encontrado";

      document.getElementById("especie")
        .innerText="";

      document.getElementById("idade")
        .innerText="";

      document.getElementById("responsavel")
        .innerText="";

      document.getElementById("uid")
        .innerText=`UID: ${pet.uid}`;

      return;
    }

    document.getElementById("nome")
      .innerText=`Nome: ${pet.nome||"-"}`;

    document.getElementById("especie")
      .innerText=`Espécie: ${pet.especie||"-"}`;

    document.getElementById("idade")
      .innerText=`Idade: ${pet.idade||"-"}`;

    document.getElementById("responsavel")
      .innerText=`Tutor: ${pet.responsavel||"-"}`;

    document.getElementById("uid")
      .innerText=`UID: ${pet.uid||"-"}`;

  }

  catch(erro){

    console.log(erro);

  }

}

atualizar();

setInterval(
  atualizar,
  2000
);

const express = require("express");
const cors = require("cors");

const pets=require("./pets.json");

const app=express();

app.use(cors());
app.use(express.json());

let ultimaLeitura={};

app.get("/pets/:uid",(req,res)=>{

const pet=pets.find(
p=>p.uid===req.params.uid
);

if(!pet){

return res.status(404).json({
erro:"Pet não encontrado"
});

}

res.json(pet);

});

app.post("/ultima-leitura",(req,res)=>{

ultimaLeitura=req.body;

res.json({
status:"ok"
});

});

app.get("/ultima-leitura",(req,res)=>{

res.json(ultimaLeitura);

});

app.listen(process.env.PORT || 3000,()=>{

console.log("Servidor iniciado");

});
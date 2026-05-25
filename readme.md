# Sistema Inteligente de Identificação de Pets com RFID

## Descrição

Este projeto consiste em um sistema IoT para identificação de pets em um consultório veterinário.

Cada animal possui uma tag RFID contendo um identificador único (UID). Quando o veterinário aproxima a tag do leitor RFID, a ESP32 realiza a leitura, envia uma requisição HTTP para uma API e recebe os dados cadastrados do pet.

As informações são exibidas em um dashboard em tempo real.

---

## Objetivo

Simular um sistema de identificação automática para agilizar atendimentos veterinários utilizando conceitos de:

- Internet das Coisas (IoT)
- RFID
- Comunicação HTTP
- APIs REST
- Dashboard Web
- ESP32

---

## Tecnologias utilizadas

### Hardware (Wokwi)

- ESP32 DevKit V1
- MFRC522 RFID Reader
- LEDs:
  - Verde → sistema ligado
  - Azul → Wi-Fi conectado
  - Vermelho → falha/pet não encontrado
- Resistores 220 Ω

### Software

- Arduino/C++
- Node.js
- Express
- HTML
- CSS
- JavaScript
- Render (Hospedagem)

### Simulação

- Wokwi

---

## Arquitetura do projeto

```text
Tag RFID
    ↓
MFRC522
    ↓
ESP32
    ↓ HTTP
API Node.js (Render)
    ↓
Dados do pet
    ↓
Dashboard Web
```

---

## Fluxo de funcionamento

1. O veterinário aproxima uma tag RFID do leitor.

2. A ESP32 realiza a leitura do UID.

3. A ESP32 faz uma requisição HTTP:

```http
GET /pets/:uid
```

4. A API retorna os dados do pet:

```json
{
   "uid":"01020304",
   "nome":"Rex",
   "especie":"Cachorro",
   "idade":"4 anos",
   "responsavel":"Carlos"
}
```

5. A ESP32 envia os dados para:

```http
POST /ultima-leitura
```

6. O dashboard atualiza automaticamente.

7. Se a tag não estiver cadastrada:

- LED vermelho acende
- Dashboard exibe erro

---

## Estados dos LEDs

| LED | Função |
|------|---------|
| Verde | Sistema ligado |
| Azul | Wi-Fi conectado |
| Vermelho | Erro ou pet não encontrado |

---

## Ligações ESP32 e MFRC522

| MFRC522 | ESP32 |
|----------|--------|
| SDA | GPIO 5 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| RST | GPIO 22 |
| VCC | 3V3 |
| GND | GND |

### LEDs

| LED | GPIO |
|------|--------|
| Verde | GPIO 25 |
| Azul | GPIO 26 |
| Vermelho | GPIO 27 |

---

## Estrutura do projeto

```text
pet-tag/src/
│
├── api/
|   ├── package-locl.json
│   ├── server.js
│   ├── pets.json
│   └── package.json
│
├── dashboard/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
└── wokwi/
    ├── sketch.ino
    ├── libraries.txt
    ├── wokwi-project.txt
    └── diagram.json
```

---

## Endpoints da API

### Buscar pet por UID

```http
GET /pets/:uid
```

Exemplo:

```http
GET /pets/01020304
```

Resposta:

```json
{
   "uid":"01020304",
   "nome":"Rex",
   "especie":"Cachorro",
   "idade":"4 anos",
   "responsavel":"Carlos"
}
```

---

### Salvar última leitura

```http
POST /ultima-leitura
```

---

### Consultar última leitura

```http
GET /ultima-leitura
```

---

## Como executar

### 1. Clonar projeto

```bash
git clone URL_DO_REPOSITORIO
```

---

### 2. Instalar dependências

```bash
npm install
```

---

### 3. Executar API localmente

```bash
npm start
```

---

### 4. Executar dashboard

Abrir:

```
https://dashboard-pet.onrender.com/
```

---

### 5. Executar Wokwi

1. Abrir projeto
2. Iniciar simulação
3. Aproximar tag RFID
4. Verificar dashboard

---

## Demonstração esperada

### Pet encontrado

```text
Nome: Rex
Espécie: Cachorro
Idade: 4 anos
Tutor: Carlos
UID: 01020304
```

### Pet não encontrado

```text
Pet não encontrado

UID: AABBCCDD
```

---
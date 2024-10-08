# Estação Metereológica
## 1. Introdução

Este projeto visa desenvolver uma solução integrada para o monitoramento de condições meteorológicas, utilizando tecnologias de ponta em hardware e comunicações. Neste repositório, focaremos exclusivamente na montagem do hardware e na integração do sistema embarcado com um servidor remoto, detalhando cada componente usado, sua configuração e a interconexão necessária para a transmissão eficiente de dados.

### Diagrama de comunicação
![Diagrama_Comunicacao_ESP32](https://github.com/user-attachments/assets/55e45daf-c120-474d-b588-3f3aeb87cf61)


## 2. Materiais e métodos 

> Nota: Neste projeto foram utilizados apenas 3 sensores, mas é possivel implementar mais sensores de acordo com a quantidade de pinos livres que o ESP32 possuir.

Esta seção descreve detalhadamente os componentes e processos utilizados na construção e operação da estação meteorológica. 

### Caracterização do sistema embarcado

- [**ESP32**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/ESP32): Um módulo microcontrolador com Wi-Fi e Bluetooth integrados, ideal para aplicações IoT.
- [**DHT11**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/DHT11): Sensor de temperatura e umidade, usado para medições ambientais básicas.
- [**Pluviômetro**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/Pluviometro): Dispositivo utilizado para medir a quantidade de precipitação.
- [**Anemômetro Arduino SV10**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/Anemometro): Sensor utilizado para medir a velocidade do vento.

### Diagrama dos componentes

O diagrama abaixo define a configuração física utilizada e a interconexão dos componentes da estação meteorológica: 

![Circuito Eletrônico](https://github.com/user-attachments/assets/192fa36d-62be-40fa-8a0f-5a6529da20d1)


![image](https://github.com/user-attachments/assets/611cec55-83bc-435d-9104-6d786f9892a6)


### Configuração de Ambiente Local
Para configurar o ambiente local, siga os passos abaixo. Este arquivo deve conter informações sensíveis como SSID e senha da rede WiFi, além da URL do servidor:

1. No arquivo `general.h` faça as seguintes alterações.
2. Altere as seguintes linhas ao arquivo:
   
   ```
   String ssid =  "SeuSSID";  // Substitua pelo SSID da sua rede
   String pass =  "SuaSenha";  // Substitua pela senha da sua rede
   ```

3. No arquivo `main.c` faça as seguintes alterações.
5. Altere as seguintes linhas ao arquivo:
   
   ```
   #define BROKER_ADDRESS "000.000.0.0"  // Substitua pelo IP do seu broker
   #define BROKER_PORT       8004  // Substitua pela porta do seu broker
   #define BROKER_USE_SECURE false // Substitua se houver segurança do seu broker
   ```


### Configuração do ESP32

#### Instalação do Driver para o ESP32

1. **Baixe e Instale o Driver:**

    - Antes de conectar o ESP32 ao seu computador, é necessário instalar o driver adequado para garantir que o dispositivo seja reconhecido corretamente. Você pode encontrar o driver específico para o ESP32 no seguinte link: [Instalação do Driver para ESP32 - RoboCore](https://www.robocore.net/tutoriais/instalando-driver-do-nodemcu)
    - Siga as instruções no site para baixar e instalar o driver correspondente ao seu sistema operacional.

2. **Conectar o ESP32 ao Computador:**

    - Após a instalação do driver, conecte o ESP32 ao computador usando um cabo USB. Se tudo estiver correto, o dispositivo deverá ser reconhecido e uma nova porta COM será listada no seu sistema.

#### Configuração no Arduino IDE

3. **Instale o Arduino IDE:**

    - Se ainda não instalou, baixe e instale o Arduino IDE diretamente do site oficial: [Arduino - Software](https://www.arduino.cc/en/software)

4. **Adicione a URL de Gerenciamento de Placas do ESP32:**

    - Abra o Arduino IDE.
    - Vá em **Arquivo > Preferências**.
    - No campo "URLs Adicionais de Gerenciadores de Placas", adicione a seguinte URL para permitir a instalação do pacote do ESP32:

		```
	  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
		```

5. **Instale o Pacote do ESP32:**

    - Acesse **Ferramentas > Placa: > Gerenciador de Placas**.
    - Na barra de pesquisa, digite "ESP32".
    - Localize "esp32 by Espressif Systems" e clique em "Instalar".

6. **Selecionar a Placa ESP32 e a Porta COM:**

    - Após a instalação do pacote, vá em **Ferramentas > Placa** e selecione o modelo do seu ESP32 na lista sob o título "NodeMCU-32S".
    - Vá em **Ferramentas > Porta** e selecione a porta COM que aparece (associada ao ESP32).

### Instalação das bibliotecas necessárias no Arduino IDE

Para instalar todas as bibliotecas necessárias, abra o Arduino IDE, vá em Sketch > Incluir Biblioteca > Gerenciar Bibliotecas, e procure e instale as seguintes bibliotecas:

- Adafruit Unified Sensor by Adafruit
- ArduinoJson by Benoit
- DHT sensor library by Adafruit

### Foto da montagem física
![estação_campus](https://github.com/user-attachments/assets/d75a953b-d2bd-48a5-80e3-8c6c2d8ba26f)

### Orçamento
O levantamento dos preços de cada componente foi realizado através de pesquisa na internet, consultando sites especializados na venda de componentes eletrônicos como: Amazon, Eletrogate e Usinainfo. Como referência, o orçamento foi levantado em outubro/2024. Todos os componentes utilizados na construção da estação e descritos na subseção de caracterização do sistema embarcado estão compilados na tabela:

| Componente                                                                           | Preço    | Fonte      |
| ------------------------------------------------------------------------------------ | -------- | ---------- |
| ESP32	                                                                               | R$49.90  | Amazon     |
| DHT11                                                                                | R$10.36  | Eletrogate |
| Alojamento do Sensor de Temperatura e Umidade para Estação Meteorológica             | R$606.29 | Usinainfo  |
| Pluviômetro de Báscula Digital Arduino para Estação Meteorológica PB10               | R$719.98 | Usinainfo |
| Anemômetro Arduino para Estação Meteorológica SVDV10                                 | R$749.55 | Usinainfo  |

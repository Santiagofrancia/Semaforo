    // Elección de pines para los led
    const int carrov = 1;
    const int carroa = 2;
    const int carror = 3;
    const int verde = 4;
    const int rojo = 5;
    const int boton = 6;
     
    // Tiempo en lo que cambia de verde a rojo
    const int tiempo_verde = 12000;
         
    // Inicializa el semáforo.
    void semaforo_init(void) {
       // Enciende el led verde del carro y los demas los deja apagados
       digitalWrite(carrov, HIGH);
       digitalWrite(carror, LOW);
       digitalWrite(carroa, LOW);
     
       // Enciende el led rojo de peatones, apaga los demas.
       digitalWrite(rojo, HIGH);
       digitalWrite(verde, LOW);
    }
    
    // Cambia el led de verde a rojo de los coches.
    void semaforo_auto_rojo(void) {
       // Apaga el led rojo
       digitalWrite(carrov,  LOW);
       // Enciende el led amarrillo y parpadea hasta que termine el for
       for(int i=5; i>0; i--) {
          delay(500);
          digitalWrite(carroa, HIGH);
          delay(500);
          digitalWrite(carroa, LOW);
       }
     
       // Enciende el led rojo para coches
       digitalWrite(carror, HIGH);
    }
     
    // Sirve para cambiar de led rojo a verde hasta que pulsemos el botón
    void semaforo_espera_pulsador(void) {
       int presionado;
       long time;
       
       // Espera a que se presione el pulsador
       // Debe permanecer esperando un tiempo mínimo
       time = millis() + tiempo_verde; 
       presionado = 0;
       while(1) {
          // Lee el estado del pulsador
          if (digitalRead(boton) == LOW)
             presionado = 1;
             
          // Si ha pasado el tiempo de verde para coches
          // y se ha presionado el pulsador, salir
          if ((millis() > time) && (presionado == 1))
             break;
       }
    }
     
     // El tiempo depende del giro del potencimetro
    void semaforo_delay(void) {
       int tiempo_peatones;
       
       // Añade dos segundo mas al potenciometro
       tiempo_peatones = 2000 + 5 * analogRead(A0);
       
       // Envia la inf. al puerto para cambio de velocidad
       Serial.print("Tiempo peatones=");
       Serial.println(tiempo_peatones);
     
       // Tiempo de espera
       delay(tiempo_peatones);
    }
     
    // Cambia el semáforo de peatones a rojo
    void semaforo_peatones_rojo(void) {
       // Parpadea el led verde 3 veces
       for(int i=3; i>0; i--) {
          digitalWrite(verde, LOW);
          delay(500);
          digitalWrite(verde, HIGH);
          delay(500);
       }
     
       // Enciende el led rojo y apaga el verde de las personas
       digitalWrite(verde, LOW);
       digitalWrite(rojo, HIGH);
    }
     
     
     // Inicio del programa
     void setup() {
       // Define las salidas del arduino
       pinMode(carrov, OUTPUT);
       pinMode(carroa, OUTPUT);
       pinMode(carror, OUTPUT);
       pinMode(verde, OUTPUT);
       pinMode(rojo, OUTPUT);
     
       // Define las entrada del botón
       pinMode(boton, INPUT_PULLUP);
       
       // Inicializa el puerto de comunicaciones
       Serial.begin(9600);
       Serial.println("Semaforo iniciado");
    }
     
    void loop() {
       
       // Inicializa el semáforo
       semaforo_init();
       
       // Metodo de espera del pulsador
       semaforo_espera_pulsador();
       
       // Cambia el semáforo de color
       semaforo_auto_rojo();
       delay(1500);
     
       // Enciende el led verde para personas y apaga el rojo
       digitalWrite(rojo, LOW);
       digitalWrite(verde, HIGH);
     
       // Tiempo de espera del potenciometro
       semaforo_delay();
     
       // Cambia el semáforo a rojo de peatones
       semaforo_peatones_rojo();
     
       // Tiempo de espera para el cambio para autos
       delay(2000);
   
    }
     

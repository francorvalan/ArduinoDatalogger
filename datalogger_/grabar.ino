// Funcion para grabar fecha, hora y datos de temperatura

void grabar(){
      File myFile = SD.open("datalog.txt", FILE_WRITE);  // creo o abro el archivo y pongo nombre
       
        if (myFile) {
        myFile.print("\n");
        myFile.print(day,DEC);
        myFile.print("/");
        myFile.print(month,DEC);
        myFile.print("/");
        myFile.print(year,DEC);
        myFile.print(" ");
        myFile.print(hour,DEC);
        myFile.print(":");
        myFile.print(minute,DEC);
        myFile.print(":");
        myFile.print(second,DEC);
        myFile.print("\t");
        
        myFile.print("Temperatura sensor 0-1-2");
        myFile.print("\t");
        
        myFile.print(t1);
        myFile.print("\t");
        
        myFile.print(t2);
        myFile.print("\t");
        
        myFile.print(t3);
        myFile.close(); // cierro el archivo
        
        }
}

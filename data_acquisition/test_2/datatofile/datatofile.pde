import processing.serial.*;
Serial myPort;
PrintWriter output;


void setup()
{
  myPort = new Serial(this, "COM8", 19200);
  output = createWriter("datalog.csv");
}

void draw()
{
  
  if (myPort.available() > 0)
  {
    String data = (myPort.readString());
    if (data != null)
    {
      output.print(data);
      print(data);
    //output.println(myPort.readString());
    }
  }
}


void keyPressed() {
  output.flush();  // Writes the remaining data to the file
  output.close();  // Finishes the file
  exit();  // Stops the program
}

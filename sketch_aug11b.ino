//incoming data stored as longs
long data[3];

// This will be the buffered string from Serial.read()
// up until you hit a \n
String str = "";

// Keep track of current position in array
int counter = 0;

// Keep track of the last comma so we know where to start the substring
int lastIndex = 0;


void setup(){
  Serial.begin(9600);
  
}

void loop(){
  
  //if there is data coming in from serial
  if (Serial.available() > 0) {
    
    //read the first byte and store it as a char type
    char ch = Serial.read();
    
    //if we find a newline character, it means we got to the end of the string so lets do something
    if (ch == '\n') {

      //lets loop through each character in the string
      for (int i = 0; i < str.length(); i++) {
        
        // check if it's a comma
        if (str.substring(i, i+1) == ",") {

          // Grab the piece from the last index up to the current position and store it temporarily
          String tempString = str.substring(lastIndex, i);
          
          // Then convert that temporary string to an int and store that
          data[counter] = tempString.toInt();
          
          // Update the last position and add 1, so it starts from the next character
          lastIndex = i + 1;
          
          // Increase the position in the array that we store into
          counter++;

        }

        //If we're at the end of the string (no more commas to stop us)
        if (i == str.length() - 1) {
          //grab the last part of the string from the lastIndex to the end
          String tempString = str.substring(lastIndex);
          //And convert to int
          data[counter] = tempString.toInt();
        }

      }   

      //clear out string and counters to get ready for the next incoming string
      str = "";
      counter = 0;
      lastIndex = 0;
    }
    else {
      
      //if we havent reached a newline character yet, add the current character to the string
      str += ch;
    }

  }

  Serial.println(data[0]);
  //data now available in the data[] array

}


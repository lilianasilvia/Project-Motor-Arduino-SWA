const char PAGINA[] = R"rawliteral(
<!DOCTYPE html>
 <html>
 <head>
      <meta name="viewport" content="width=device-width,initial-scale=1">
    <title></title>
    <style>
      body {
        background-color: rgba(180,180,180,1);
        text-align: center
      }

      * {
        box-sizing: border-box;
      }

      .mode_button {
        background-color: rgba(120,120,120,1);
        border-radius: 15px;
        width: 100%;
        
        padding: 10px;
        
        border-style: solid;
        border-width: 5px;
        border-color: rgba(180,180,180,1);
        
        display: block;
        
        text-align: center;
        color: black;
      }

      .buttons_container {
        background-color: rgba(200,200,200,0);
        border-radius: 15px;
        width: 90%;
        max-width: 500px;
        
        /*padding: 5px;*/
        border-style: solid;
        border-width: 5px;
        border-color: rgba(180,180,180,1);
        
        margin: 0 auto;
        
        display: block;

        color: black;
        
      }

      .status_container {
        background-color: rgba(200,200,200,0);
        border-radius: 15px;
        width: 90%;
        height: 450px;;
        max-width: 500px;
        
        /*padding: 5px;*/
        border-style: solid;
        border-width: 5px;
        border-color: rgba(180,180,180,1);
        
        margin: 0 auto;
        
        display: block;
        vertical-align: top;

        color: black;
        
      }

      .start_stop_container {
        background-color: rgba(240,240,240,0);
        border-radius: 15px;
        width: 100%;
        height: 20%;
        
        /*padding: 5px;*/
        border-style: solid;
        border-width: 0px;
        border-color: rgba(180,180,180,1);
        
        display: block;
        
        text-align: left;
        vertical-align: top;
        
        color: black;
        
      }

      .status_display {
        background-color: rgba(220,220,220,1);
        border-radius: 15px;
        width: 100%;
        height: 80%;
        
        padding: 5px;
        border-style: solid;
        border-width: 5px;
        border-color: rgba(180,180,180,1);
        
        display: block;
        
        text-align: center;
        vertical-align: top;
        
        color: black;
        
      }

      

      .start_button, .stop_button {
        background-color: rgba(120,180,120,1);
        border-radius: 15px;
        width: 50%;
        
        padding: 25px 0;
        border-style: solid;
        border-width: 5px;
        border-color: rgba(180,180,180,1);
        
        margin: 0 auto;
        
        display: inline-block;
        
        text-align: center;
        color: black;
        
      }

      .start_button {
        background-color: rgba(120,160,120,1);
      }

      .stop_button {
        background-color: rgba(160,120,120,1);
      }
      
      .temp_humid {
        background-color: rgba(220,220,220,1);
        border-radius: 15px;
        width: 90%;
        max-width: 500px;
        
        padding: 20px;
        border-style: solid;
        border-width: 5px;
        border-color: rgba(180,180,180,1);
        
        margin: 0 auto;
        
        display: block;

        color: black;
        
      }

      @media only screen and (min-device-width: 640px) {
        .mode_button {
          width: 100%;        
          display: block;   
        } 
        .temp_humid, .status_container {
          max-width: 1000px;
          height: 15%;
        }
        .buttons_container {
          display: inline-block;
          width: 25%;
          height: 85%;
        }
        .status_container {
          display: inline-block;
          width: 75%;
          height: 85%;
        }
        .status_display {
          display: inline-block;
          width: 80%;
          height: 100%;
        }
         .start_stop_container {
          display: inline-block;
          width: 20%;
          height: 100%;
        }
        .start_button, .stop_button {
          width: 100%;
          padding: 50px 0;
        }
      }
    </style>
  </head>
<body><!--
  --><div id="buttons_container" class="buttons_container"><!--
    --><div id="mode_button_1" class="mode_button" onclick="button_press(1)">
      Line follower
    </div><!--
    --><div id="mode_button_2" class="mode_button" onclick="button_press(2)">
      Hand follower
    </div><!--
    --><div id="mode_button_3" class="mode_button" onclick="button_press(3)">
      Obstacle avoider
    </div><!--
  --></div><!--
  --><div id="status_container" class="status_container"><!--
    --><div id="status_display" class="status_display">
        Status
        <br>
        <img src="https://i.imgur.com/aotmGEf.png" height="180px" width="180px" id="status_icon">
    </div><!--
      --><div id="start_stop_container" class="start_stop_container"><!--
        --><div id="start_button" class="start_button" onclick="">
            START
          </div><!--
        --><div id="stop_button" class="stop_button" onclick="window.alert(screen.width)">
            STOP
          </div><!--
      --></div><!--
  --></div><!--
  --><div id="temp_humid" class="temp_humid">
    Temperature / Humidity
  </div><!--
  --><script type="text/javascript">
      var status_icon_happy = "happy https://i.imgur.com/sgtkAhv.png";
      var status_icon_sad = "https://i.imgur.com/TEyTI63.png";
      var status_icon_up = "https://i.imgur.com/AbAQtAt.png";
      var status_icon_down = "https://i.imgur.com/v2LvgtS.png";
      var status_icon_right = "https://i.imgur.com/fIpcnET.png";
      var status_icon_left = "https://i.imgur.com/vpYVSg0.png";
      var status_icon_stop = "https://i.imgur.com/8CwAxin.png";

      var status_icons = ["https://i.imgur.com/sgtkAhv.png", "https://i.imgur.com/TEyTI63.png", "https://i.imgur.com/AbAQtAt.png", "https://i.imgur.com/v2LvgtS.png", "https://i.imgur.com/fIpcnET.png", "https://i.imgur.com/vpYVSg0.png", "https://i.imgur.com/8CwAxin.png"];

      var i=0, t=0;

      var status_icon_element = document.getElementById("status_icon");
      var status_text_element = document.getElementById("status_text");
      var temp_humid_element = document.getElementById("temp_humid");
      
      var mode_1_button = document.getElementById("mode_button_1");
      var mode_2_button = document.getElementById("mode_button_2");
      var mode_3_button = document.getElementById("mode_button_3");

     

      function get_temp_humid(){

        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
           if (this.readyState == 4 && this.status == 200) {
             temp_humid_element.innerHTML = this.responseText;
          }
        };
       xhttp.open("GET", "/temperature_humidity", true);
       xhttp.send();
       
      }

      function get_mode(){

        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
           if (this.readyState == 4 && this.status == 200) {
            //change collor to grey to all 3 buttons
            mode_1_button.style.backgroundColor = "rgba(120,120,120,1)"; //grey
            mode_2_button.style.backgroundColor = "rgba(120,120,120,1)";
            mode_3_button.style.backgroundColor = "rgba(120,120,120,1)";

            switch(this.responseText){
              case "1":
                mode_1_button.style.backgroundColor = "green";
                break;
              case "2":
                mode_2_button.style.backgroundColor = "green";
                break;
              case "3":
                mode_3_button.style.backgroundColor = "green";
                break;
            }
          }
        };
       xhttp.open("GET", "/get_mode", true);
       xhttp.send();
       
      }

      function get_graphic_status(){

        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
           if (this.readyState == 4 && this.status == 200) {
            switch(this.responseText){
              case "10":
                status_icon_element.src = status_icon_left;
                break;
              case "20":
                status_icon_element.src = status_icon_up;
                break;
              case "30":
                status_icon_element.src = status_icon_right;
                break;
              case "40":
                status_icon_element.src = status_icon_down;
                break;
              case "50":
                status_icon_element.src = status_icon_happy;
                break;
              case "60":
                status_icon_element.src = status_icon_sad;
                break;
              case "70":
                status_icon_element.src = status_icon_stop;
                break;
            }
          }
        };
       xhttp.open("GET", "/get_graphic_status", true);
       xhttp.send();
       
      }

      function button_press(m)
      {
        //change collor to grey to all 3 buttons
            mode_1_button.style.backgroundColor = "rgba(120,120,120,1)"; //grey
            mode_2_button.style.backgroundColor = "rgba(120,120,120,1)";
            mode_3_button.style.backgroundColor = "rgba(120,120,120,1)";
            
        switch(m){
          case 1:
            mode_1_button.style.backgroundColor = "rgba(120,120,200,1)"; //blueish
            break;
          case 2:
            mode_2_button.style.backgroundColor = "rgba(120,120,200,1)"; //blueish
            break;
          case 3:
            mode_3_button.style.backgroundColor = "rgba(120,120,200,1)"; //blueish
            break;
        }
        //send new mode to Wemos
        var xhttp = new XMLHttpRequest();
       xhttp.open("GET", "/set_mode?m=" + m, true);
       xhttp.send();
      }

      
      setInterval(get_temp_humid, 1000);
      setInterval(get_mode, 1000);
      setInterval(get_graphic_status, 200);
  </script></body>
)rawliteral";

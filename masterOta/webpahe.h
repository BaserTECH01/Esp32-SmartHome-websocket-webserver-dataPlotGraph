//=====================
//HTML code for webpage
//=====================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE HTML>
<html>
<title>ESP32 WebSocket Server</title>
<!---------------------------CSS-------------------------->
<style>

    body   {background-color:rgba(128,128,128,0.322); font-family:calibri}
    h1     {font-size: 40px; color: black; text-align: center}
    
    h3     {font-size: 17px; color:blue}
    div.h1 {background-color: whitesmoke;}

    table, th, td {
     border: 2px solid black;
     border-radius: 7px;
    
    }
    td{
        style="width:40%"
    }
    th, td{
        text-align: center;
        font-size: 300%
    }
    th{
        style="width:60%"
        
    }
    tr:nth-child(even) {
     background-color: #D6EEEE;
    }
    

    .button {
      padding: 15px 25px;
      font-size: 24px;
      text-align: center;
      cursor: pointer;
      outline: none;
      color: #fff;
      background-color: #04AA6D;
      border: none;
      border-radius: 15px;
      box-shadow: 0 9px #999;
    }

    .button:hover {background-color: #3e8e41}

    .button:active {
     background-color: #3e8e41;
     box-shadow: 0 5px #666;
     transform: translateY(4px);
    }




    .switch {
  position: relative;
  display: inline-block;
  width: 60px;
  height: 34px;
}

.switch input { 
  opacity: 0;
  width: 0;
  height: 0;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}

.slider:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}

input:checked + .slider {
  background-color: #2196F3;
}

input:focus + .slider {
  box-shadow: 0 0 1px #2196F3;
}

input:checked + .slider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}


    
    
</style>
<!--------------------------HTML-------------------------->
<body>
    <h1><div class="h1">ESP32 WebSocket Server</div></h1>
 <center>
 <a href="http://192.168.1.43/serverIndex" target="_blank" rel="noopener noreferrer">
 <button class="button" style="background-color:rgb(3, 30, 223)" >Update for firmware of master</button>
 
 </a>
  <a href="http://192.168.1.44:90/serverIndex" target="_blank" rel="noopener noreferrer">
 <button class="button" style="background-color:rgb(3, 115, 3)" >Update for firmware of Slave </button>
 <p>Updated from ngrok tunnel</p>
 </a>
 <div >
 <a style=rgba(128,128,128,0.322) ></a>
 </div>
 </center>
    <table style="width:100%" >
  <tr style="height:150px">
    <th>Boards</th>
    <th>Watts</th> 
    <th>Currents</th>
    <th>State</th>
    <th>Mode</th>
    <th>1.State</th>
    <th>2.State</th>
  </tr>
  <tr style="height:100px">
    <td>Board 1</td>
    <td><span style="color:rgb(216, 3, 3)" id="board1V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board1C">0</span> A</td>
    <th><button class="button"  id="btn"  onclick="button()" > </button></td>
    <th><p id="mode1"></p><label class="switch"> 
  <input type="checkbox">
  <span class="slider"></span>
</label></td>
  </tr>
  <tr style="height:100px">
    <td>Board 2</td>
    <td><span style="color:rgb(216, 3, 3)" id="board2V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board2C">0</span> A</td>
    <th><button class="button"  id="btn2"  onclick="button2()" > </button></td>
  </tr>
  <tr style="height:100px">
    <td>Board 3</td>
    <td><span style="color:rgb(216, 3, 3)" id="board3V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board3C">0</span> A</td>
    <th><button class="button"  id="btn3"  onclick="button3()" > </button></td>
  </tr>
  <tr style="height:100px">
    <td>Board 4</td>
    <td><span style="color:rgb(216, 3, 3)" id="board4V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board4C">0</span> A</td>
    <th>ON</td>
  </tr>
  <tr style="height:100px">
    <td>Board 5</td>
    <td><span style="color:rgb(216, 3, 3)" id="board5V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board5C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 5</td>
    <td><span style="color:rgb(216, 3, 3)" id="board5V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board5C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 6</td>
    <td><span style="color:rgb(216, 3, 3)" id="board6V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board6C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 7</td>
    <td><span style="color:rgb(216, 3, 3)" id="board7V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board7C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 8</td>
    <td><span style="color:rgb(216, 3, 3)" id="board8V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board8C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 9</td>
    <td><span style="color:rgb(216, 3, 3)" id="board9V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board9C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 10</td>
    <td><span style="color:rgb(216, 3, 3)" id="board10V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board10C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 11</td>
    <td><span style="color:rgb(216, 3, 3)" id="board11V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board11C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 12</td>
    <td><span style="color:rgb(216, 3, 3)" id="board12V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board12C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 13</td>
    <td><span style="color:rgb(216, 3, 3)" id="board13V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board13C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 14</td>
    <td><span style="color:rgb(216, 3, 3)" id="board14V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board14C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 15</td>
    <td><span style="color:rgb(216, 3, 3)" id="board15V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board15C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 16</td>
    <td><span style="color:rgb(216, 3, 3)" id="board16V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board16C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 17</td>
    <td><span style="color:rgb(216, 3, 3)" id="board17V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board17C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 18</td>
    <td><span style="color:rgb(216, 3, 3)" id="board18V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board18C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 19</td>
    <td><span style="color:rgb(216, 3, 3)" id="board19V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board19C">0</span> A</td>
    <th>ON</td>
  </tr>

  <tr style="height:100px">
    <td>Board 20</td>
    <td><span style="color:rgb(216, 3, 3)" id="board20V">0</span> V </td>
    <td><span style="color:rgb(15, 56, 245)" id="board20C">0</span> A</td>
    <th>ON</td>
  </tr>
      
 </table>
 
</body>
<!----------------------JavaScript------------------------>
<script>
  InitWebSocket()
  function InitWebSocket()
  {
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    websock.onmessage=function(evt)
    {
      
      JSONobj = JSON.parse(evt.data);
          
           document.getElementById('board1V').innerHTML = JSONobj.brd1V;
           document.getElementById('board1C').innerHTML = JSONobj.brd1C;
           document.getElementById('board2V').innerHTML = JSONobj.brd2V;
           document.getElementById('board2C').innerHTML = JSONobj.brd2C;
           document.getElementById('board3V').innerHTML = JSONobj.brd3V;
           document.getElementById('board3C').innerHTML = JSONobj.brd3C;
          
          //1. BUTON
          if(JSONobj.brd1S == 'ON')
          {
            document.getElementById('btn').innerHTML = JSONobj.brd1S;
            document.getElementById('btn').style.background = '#3e8e41';
          }
          else if(JSONobj.brd1S == 'OFF')
          {
            document.getElementById('btn').innerHTML = JSONobj.brd1S;
            document.getElementById('btn').style.background='#d40505';
          }


          //2. BUTON
          if(JSONobj.brd2S == 'ON')
          {
            document.getElementById('btn2').innerHTML = JSONobj.brd2S;
            document.getElementById('btn2').style.background = '#3e8e41';
          }
          else if(JSONobj.brd2S == 'OFF')
          {
            document.getElementById('btn2').innerHTML = JSONobj.brd2S;
            document.getElementById('btn2').style.background='#d40505';
          }


          //3. BUTON
          if(JSONobj.brd3S == 'ON')
          {
            document.getElementById('btn3').innerHTML = JSONobj.brd3S;
            document.getElementById('btn3').style.background = '#3e8e41';
          }
          else if(JSONobj.brd3S == 'OFF')
          {
            document.getElementById('btn3').innerHTML = JSONobj.brd3S;
            document.getElementById('btn3').style.background='#d40505';
          }
       
       


    }
  }
  

  function button()
     {
        
        if(document.getElementById("btn").innerHTML == 'ON')
        {
          btn = "brd1S=OFF";
        }
        else if(document.getElementById("btn").innerHTML == 'OFF')
        {
          btn = "brd1S=ON";
        }
        websock.send(btn);
     }

  function button2()
     {
        
        if(document.getElementById("btn2").innerHTML == 'ON')
        {
          btn2 = "brd2S=OFF";
        }
        else if(document.getElementById("btn2").innerHTML == 'OFF')
        {
          btn2 = "brd2S=ON";
        }
        websock.send(btn2);
     }
      
   function button3()
     {
        
        if(document.getElementById("btn3").innerHTML == 'ON')
        {
          btn3 = "brd3S=OFF";
        }
        else if(document.getElementById("btn3").innerHTML == 'OFF')
        {
          btn3 = "brd3S=ON";
        }
        websock.send(btn3);
     }     



</script>
</html>
)=====";

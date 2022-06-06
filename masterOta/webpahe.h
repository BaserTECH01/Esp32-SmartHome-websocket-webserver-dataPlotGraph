//=====================
//HTML code for webpage
//=====================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE HTML>
<html>
<title>ESP32 WebSocket Server</title>
<head>
  <script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js'></script>
</head>


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
        font-size: 150%
    }
    th{
        style="width:60%"
        
    }
    tr:nth-child(even) {
     background-color: #D6EEEE;
    }
    

    .button {
      padding: 15px 25px;
      font-size: 20px;
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

    .buttonMinik {
      padding: 9px 9px;
      font-size: 12px;
      text-align: center;
      cursor: pointer;
      outline: none;
      color: #fff;
      background-color: #04AA6D;
      border: none;
      border-radius: 7px;
      box-shadow: 0 4px #999;
    }

    .buttonMinik:hover {background-color: #3e8e41}

    .buttonMinik:active {
     background-color: #3e8e41;
     box-shadow: 0 3px #666;
     transform: translateY(3px);
    }

    input {
     width:40%;
     height:10%;
   }


canvas {
  border: 3px outset red;
  background-color: lightblue;
  border-radius: 7px; 
}

.chart-container {
  margin:5%;
  display: flex;
  flex-wrap: nowrap;
  width: 45%;
  
}

</style>
<!--------------------------HTML-------------------------->
<body onload="javascript:solar()">
<h1><div class="h1">Smart Home Dashboard</div></h1>

    <div>
 <center>
 <a href="http://192.168.1.43/serverIndex" target="_blank" rel="noopener noreferrer">
 <button class="button" style="background-color:rgb(3, 30, 223)" >Update for firmware of master</button>
 </a>
 <p></p>
<br>
</div>



 <div >
 <a style=rgba(128,128,128,0.322) ></a>
 </div>
 </center>
 


<div class="chart-container">

    <canvas id="line-chart" ></canvas>  
  <p style="color:rgba(214,214,214,255)" >a</p>
    <canvas id="chart_solar" ></canvas> 
  
</div>

    <table style="width:100%" >
  <tr style="height:50px">
    <th>Boards</th>
    <th>Watts</th> 
    <th>Currents</th>
    <th>State</th>
    <th>Mode</th>
    <th>Timer</th>

  </tr>
  
  <tr style="height:100px">
    <td><p>board 1</p><p style="color:red;" id="brd1connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board1V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board1C">0</span> A</td>
    <th><button class="button"  id="btn"  onclick="button()" > </button></td>
    <th><button class="button"  id="Mbtn1"  onclick="Mod1()" ></button></td>
    <th>     <select disabled="true" id="brd1timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="number" disabled="true" id="brd1BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="number" disabled="true" id="brd1BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="number" disabled="true" id="brd1SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="number" disabled="true" id="brd1SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="sendinput()">send</button><br><br>
        
    </td>  
  </tr> 
  
  <tr style="height:100px">
    <td><p>board 2</p><p style="color:red;" id="brd2connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board2V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board2C">0</span> A</td>
    <th><button class="button"  id="btn2"  onclick="button2()" > </button></td>
    <th><button class="button"  id="Mbtn2"  onclick="Mod2()" ></button></td>
    <th>     <select disabled="true" id="brd2timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>    
        <input type ="number" disabled="true" id="brd2BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
        <input type ="number" disabled="true" id="brd2BasD1" min="0" max="59" placeholder="Start Min"></input><br>
        <input type ="number" disabled="true" id="brd2SonS1" min="0" max="23" placeholder="End Hour"></input><br>
        <input type ="number" disabled="true" id="brd2SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd2time()">send</button><br><br>
    </td>  
  </tr>
  
  <tr style="height:100px">
    <td><p>board 3</p><p style="color:red;" id="brd3connectStatus" >Connection</p></td>
    <td><span style="color:rgb(216, 3, 3)" id="board3V">0</span> W </td>
    <td><span style="color:rgb(15, 56, 245)" id="board3C">0</span> A</td>
    <th><button class="button"  id="btn3"  onclick="button3()" > </button></td>
    <th><button class="button"  id="Mbtn3"  onclick="Mod3()" ></button></td>
    <th>     <select disabled="true" id="brd3timerNo" required>
               <option value="" selected disabled>Timer interval no</option>
               <option value="1">1</option>
               <option value="2">2</option>
               <option value="3">3</option>
             </select>
             <br>
         <input type ="number" disabled="true" id="brd3BasS1" min="0" max="23" placeholder="Start Hour"></input><br>
         <input type ="number" disabled="true" id="brd3BasD1" min="0" max="59" placeholder="Start Min"></input><br>
         <input type ="number" disabled="true" id="brd3SonS1" min="0" max="23" placeholder="End Hour"></input><br>
         <input type ="number" disabled="true" id="brd3SonD1" min="0" max="59" placeholder="End Min"></input><br>
        <button class="buttonMinik" onclick="brd3time()">send</button><br><br>
        
    </td>
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
  var dataPlot;
  var dataPlot2;
  var maxDataPoints = 20;
  function removeData(){
    dataPlot.data.labels.shift();
    dataPlot.data.datasets[0].data.shift();
    dataPlot.data.datasets[1].data.shift();
  }
  function addData(label, data) {
    if(dataPlot.data.labels.length > maxDataPoints) removeData(); 
    dataPlot.data.datasets[0].data.push(data);
    dataPlot.update();
  }
  function addData2(label, data) {
    dataPlot.data.labels.push(label);
    dataPlot.data.datasets[1].data.push(data);
    dataPlot.update();
  }

  
  function solar()
     {
        
       dataPlot2 = new Chart(document.getElementById("chart_solar"), {
       type: 'line',
        data: {
          labels: [1,2,3,4,5,6,7,8,9,10],
          datasets: [{
          data: [10,20,120,50,80,60,50,40,30,90],
          label: "Solar panel Power",
          borderColor: "red",
          fill: false
            }]
        }
          });
        dataPlot2.data.datasets[0].data.push(data);       
        dataPlot2.update();

       } 

    

  
  InitWebSocket()
  function InitWebSocket()
  {
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    
      dataPlot = new Chart(document.getElementById("line-chart"), {
      type: 'line',
      data: {
        labels: [],
        datasets: [{
          data: [],
          label: "Board 3 Current (A)",
          borderColor: "red",
          fill: false
        },
        {
          data: [1],
          label: "Board 2 Current (A)",
          borderColor: "blue",
          fill: false
        }]
        
      }
    });
    websock.onmessage=function(evt)
    {
      
      JSONobj = JSON.parse(evt.data);

      


      
        if(JSONobj.brd1V){


      
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

          
          
          document.getElementById('board1V').innerHTML = JSONobj.brd1V;
          document.getElementById('board1C').innerHTML = JSONobj.brd1C;
          
          if(JSONobj.brd1M=='Manuel'){
          document.getElementById("btn").disabled = false;
          document.getElementById("brd1timerNo").disabled = true;
          document.getElementById("brd1BasS1").disabled = true;
          document.getElementById("brd1BasD1").disabled = true;
          document.getElementById("brd1SonS1").disabled = true;
          document.getElementById("brd1SonD1").disabled = true;
                
          document.getElementById('Mbtn1').innerHTML = JSONobj.brd1M;
          document.getElementById('Mbtn1').style.background = 'blue';
          }
          
          if(JSONobj.brd1M=='Timer'){
            document.getElementById("btn").disabled = true;
            document.getElementById("brd1timerNo").disabled = false;
            document.getElementById("brd1BasS1").disabled = false;
            document.getElementById("brd1BasD1").disabled = false;
            document.getElementById("brd1SonS1").disabled = false;
            document.getElementById("brd1SonD1").disabled = false;
                        
            document.getElementById('Mbtn1').innerHTML = JSONobj.brd1M;
            document.getElementById('Mbtn1').style.background = 'green';
          }



          if(JSONobj.brd1ConnectSt == 'Connected')
          {
            document.getElementById('brd1connectStatus').innerHTML = JSONobj.brd1ConnectSt;
            document.getElementById('brd1connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd1ConnectSt == 'No Connection')
          {
            document.getElementById('brd1connectStatus').innerHTML = JSONobj.brd1ConnectSt;
            document.getElementById('brd1connectStatus').style.color = '#d40505';
          }
          
        }

        //----------------Board---2-------------------------
          if(JSONobj.brd2V)
          {
      var today = new Date();
      var t = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();

      addData2(t, JSONobj.brd2C);
            
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

          
           document.getElementById('board2V').innerHTML = JSONobj.brd2V;
           document.getElementById('board2C').innerHTML = JSONobj.brd2C;

           if(JSONobj.brd2M=='Manuel'){
          document.getElementById("btn2").disabled = false;
          document.getElementById("brd2timerNo").disabled = true;
          document.getElementById("brd2BasS1").disabled = true;
          document.getElementById("brd2BasD1").disabled = true;
          document.getElementById("brd2SonS1").disabled = true;
          document.getElementById("brd2SonD1").disabled = true;
                
          document.getElementById('Mbtn2').innerHTML = JSONobj.brd2M;
          document.getElementById('Mbtn2').style.background = 'blue';            
           }

          if(JSONobj.brd2M=='Timer'){
            document.getElementById("btn2").disabled = true;
            document.getElementById("brd2timerNo").disabled = false;
            document.getElementById("brd2BasS1").disabled = false;
            document.getElementById("brd2BasD1").disabled = false;
            document.getElementById("brd2SonS1").disabled = false;
            document.getElementById("brd2SonD1").disabled = false;
                        
            document.getElementById('Mbtn2').innerHTML = JSONobj.brd2M;
            document.getElementById('Mbtn2').style.background = 'green';
          }
           
           if(JSONobj.brd2ConnectSt == 'Connected')
          {
            document.getElementById('brd2connectStatus').innerHTML = JSONobj.brd2ConnectSt;
            document.getElementById('brd2connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd2ConnectSt == 'No Connection')
          {
            document.getElementById('brd2connectStatus').innerHTML = JSONobj.brd2ConnectSt;
            document.getElementById('brd2connectStatus').style.color = '#d40505';
          }

          }


          //---------------Board--3-----------

          if(JSONobj.brd3V)
          {

      addData(t, JSONobj.brd3C);

                  
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

          
           document.getElementById('board3V').innerHTML = JSONobj.brd3V;
           document.getElementById('board3C').innerHTML = JSONobj.brd3C;

           if(JSONobj.brd3M=='Manuel'){
          document.getElementById("btn3").disabled = false;
          document.getElementById("brd3timerNo").disabled = true;
          document.getElementById("brd3BasS1").disabled = true;
          document.getElementById("brd3BasD1").disabled = true;
          document.getElementById("brd3SonS1").disabled = true;
          document.getElementById("brd3SonD1").disabled = true;
                
          document.getElementById('Mbtn3').innerHTML = JSONobj.brd3M;
          document.getElementById('Mbtn3').style.background = 'blue';            
           }

          if(JSONobj.brd3M=='Timer'){
            document.getElementById("btn3").disabled = true;
            document.getElementById("brd3timerNo").disabled = false;
            document.getElementById("brd3BasS1").disabled = false;
            document.getElementById("brd3BasD1").disabled = false;
            document.getElementById("brd3SonS1").disabled = false;
            document.getElementById("brd3SonD1").disabled = false;
                        
            document.getElementById('Mbtn3').innerHTML = JSONobj.brd3M;
            document.getElementById('Mbtn3').style.background = 'green';
          }
           
           if(JSONobj.brd3ConnectSt == 'Connected')
          {
            document.getElementById('brd3connectStatus').innerHTML = JSONobj.brd3ConnectSt;
            document.getElementById('brd3connectStatus').style.color = '#3e8e41';
          }

           if(JSONobj.brd3ConnectSt == 'No Connection')
          {
            document.getElementById('brd3connectStatus').innerHTML = JSONobj.brd3ConnectSt;
            document.getElementById('brd3connectStatus').style.color = '#d40505';
          }

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

    function Mod1()
    {
      if(document.getElementById("Mbtn1").innerHTML == 'Timer')
        {
          Mbtn1 = "Mode1=Manuel";
        }
        else if(document.getElementById("Mbtn1").innerHTML == 'Manuel')
        {
          Mbtn1 = "Mode1=Timer";
        }
        websock.send(Mbtn1);
           
    }

    function Mod2()
    {
      if(document.getElementById("Mbtn2").innerHTML == 'Timer')
        {
          Mbtn2 = "Mode2=Manuel";
        }
        else if(document.getElementById("Mbtn2").innerHTML == 'Manuel')
        {
          Mbtn2 = "Mode2=Timer";
        }
        websock.send(Mbtn2);
           
    }

    function Mod3()
    {
      if(document.getElementById("Mbtn3").innerHTML == 'Timer')
        {
          Mbtn3 = "Mode3=Manuel";
        }
        else if(document.getElementById("Mbtn3").innerHTML == 'Manuel')
        {
          Mbtn3 = "Mode3=Timer";
        }
        websock.send(Mbtn3);
           
    }    

    
    function sendinput()
    {
       var BasSaatdk = document.getElementById("brd1BasS1").value*60;
       var basdk = document.getElementById("brd1BasD1").value;
       var sonSaatdk = document.getElementById("brd1SonS1").value*60;
       var sondk = document.getElementById("brd1SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd1timerNo").value ==1){
        brd1time1 = "brd1time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd1time1);
       }
       if ( document.getElementById("brd1timerNo").value ==2){
        brd1time2 = "brd1time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd1time2);
       }       

    }
    

    function brd2time()
    {
       var BasSaatdk = document.getElementById("brd2BasS1").value*60;
       var basdk = document.getElementById("brd2BasD1").value;
       var sonSaatdk = document.getElementById("brd2SonS1").value*60;
       var sondk = document.getElementById("brd2SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       brd2time1 = "brd2time1="+"bas="+basTdk+"Son="+sonTdk;
       console.log(brd2time1);
      websock.send(brd2time1);
    }

    function brd3time()
    {
       var BasSaatdk = document.getElementById("brd3BasS1").value*60;
       var basdk = document.getElementById("brd3BasD1").value;
       var sonSaatdk = document.getElementById("brd3SonS1").value*60;
       var sondk = document.getElementById("brd3SonD1").value;
       var basTdk = parseInt(BasSaatdk) + parseInt(basdk) ;
       var sonTdk = parseInt(sonSaatdk) + parseInt(sondk) ;
       console.log(basTdk);
       console.log(sonTdk);
       if ( document.getElementById("brd3timerNo").value ==1){
        brd3time1 = "brd3time1="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd3time1);
       }
       if ( document.getElementById("brd3timerNo").value ==2){
        brd3time2 = "brd3time2="+"bas="+basTdk+"Son="+sonTdk;
        websock.send(brd3time2);       }  
    }    



</script>
</html>
)=====";

// Crear grafico para el servo 1
var servo1 = new RadialGauge({
  renderTo: 'servo1',
  width: 300,
  height: 300,
  units: "Servo 1",
  minValue: 0,
  maxValue: 180,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 2,
  majorTicks: [
      "0",
      "20",
      "40",
      "60",
      "80",
      "100",
      "120",
      "140",
      "160",
      "180"

  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 160,
          "to": 180,
          "color": "#03C0C1"
      }
  ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();

// Crear grafico para el servo 2
var servo2 = new RadialGauge({
  renderTo: 'servo2',
  width: 300,
  height: 300,
  units: "Servo 1",
  minValue: 0,
  maxValue: 180,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 2,
  majorTicks: [
      "0",
      "20",
      "40",
      "60",
      "80",
      "100",
      "120",
      "140",
      "160",
      "180"

  ],
  minorTicks: 4,
  strokeTicks: true,
  highlights: [
      {
          "from": 160,
          "to": 180,
          "color": "#03C0C1"
      }
  ],
  colorPlate: "#fff",
  borderShadowWidth: 0,
  borders: false,
  needleType: "line",
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  animationDuration: 1500,
  animationRule: "linear"
}).draw();

function updateTextInput1(val) {
  console.log(val);
  document.getElementById('pwmInput1').value = val; 
  document.getElementById('textInput1').value = val;
  servo1.value = val;
}
function updateTextInput2(val) {
  console.log(val);
  document.getElementById('pwmInput2').value = val; 
  document.getElementById('textInput2').value = val; 
  servo2.value = val;
}
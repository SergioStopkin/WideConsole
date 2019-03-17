## 1. Chart
### *Print()*
```
                    ▴                
1.5 ················│················
1.3 ················│················
1.1 ················│················
0.9 ················│··········••••••
0.8 ••··············│·········••·····
0.6 ·•••············│········••······
0.4 ···••···········│·······••·······
0.2 ····••··········│······•·········
0.0 ─────••─────────┼─────••─────────▸
-0.2······••········│····•···········
-0.4·······••·······│···•············
-0.6········••······│·••·············
-0.8·········•••····│••··············
-0.9···········•••••••···············
-1.1················│················
-1.3················│················
-1.5················│················
    -1.5 -1.0 -0.6 -0.1 0.3 0.7 1.0 1.4
```

```diff
+ this text is highlighted in green
- this text is highlighted in red
```

```json
   {
     "aliceblue": "#f0f8ff",
     "antiquewhite": "#faebd7",
     "aqua": "#00ffff",
     "aquamarine": "#7fffd4",
     "azure": "#f0ffff",
     "beige": "#f5f5dc",
     "bisque": "#ffe4c4",
     "black": "#000000",
     "blanchedalmond": "#ffebcd",
     "blue": "#0000ff",
     "blueviolet": "#8a2be2",
     "brown": "#a52a2a"
   }
```

```json
{
  "aliceblue": [240, 248, 255, 1],
  "antiquewhite": [250, 235, 215, 1],
  "aqua": [0, 255, 255, 1],
  "aquamarine": [127, 255, 212, 1],
  "azure": [240, 255, 255, 1],
  "beige": [245, 245, 220, 1],
  "bisque": [255, 228, 196, 1],
  "black": [0, 0, 0, 1],
  "blanchedalmond": [255, 235, 205, 1],
  "blue": [0, 0, 255, 1],
  "blueviolet": [138, 43, 226, 1],
  "brown": [165, 42, 42, 1],
  "burlywood": [222, 184, 135, 1],
  "cadetblue": [95, 158, 160, 1],
  "chartreuse": [127, 255, 0, 1],
  "chocolate": [210, 105, 30, 1],
  "coral": [255, 127, 80, 1]
}
```

```json
{
  "colors": [
    {
      "color": "black",
      "category": "hue",
      "type": "primary",
      "code": {
        "rgba": [255,255,255,1],
        "hex": "#000"
      }
    },
    {
      "color": "white",
      "category": "value",
      "code": {
        "rgba": [0,0,0,1],
        "hex": "#FFF"
      }
    },
    {
      "color": "red",
      "category": "hue",
      "type": "primary",
      "code": {
        "rgba": [255,0,0,1],
        "hex": "#FF0"
      }
    },
    {
      "color": "blue",
      "category": "hue",
      "type": "primary",
      "code": {
        "rgba": [0,0,255,1],
        "hex": "#00F"
      }
    },
    {
      "color": "yellow",
      "category": "hue",
      "type": "primary",
      "code": {
        "rgba": [255,255,0,1],
        "hex": "#FF0"
      }
    },
    {
      "color": "green",
      "category": "hue",
      "type": "secondary",
      "code": {
        "rgba": [0,255,0,1],
        "hex": "#0F0"
      }
    }
  ]
}
```

```html
    <font color="red">This is some text!</font>
    <p style="color:red">This is a paragraph.</p>
    <p style="color:blue">This is another paragraph.</p> 
```

```js
   <div id="about">Ok!!!</div>
   var about;
   function init() { 
     document.getElementById("about").style.color = 'blue';
   }
```

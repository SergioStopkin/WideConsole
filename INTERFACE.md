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

```html
Some Markdown text with <span style="color:blue">some *blue* text</span>
<p>Some Markdown text with <span style="color:blue">some <em>blue</em> text</span>.</p>
<span style="color:blue">some *This is Blue italic.* text</span>
<span style="color:red">some **This is Red Bold.** text</span>
```

```js
  import { Component } from '@angular/core';
  import { MovieService } from './services/movie.service';

  @Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: ['./app.component.css'],
    providers: [ MovieService ]
  })
  export class AppComponent {
    title = 'app works!';
  }
```

```diff
+ this text is highlighted in green
- this text is highlighted in red
```

![](https://placehold.it/15/ff0000/000000?text=+)
![](https://placehold.it/15/c5f015/000000?text=+)
![](https://placehold.it/15/1589F0/000000?text=+)

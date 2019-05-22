```plantuml
@startuml

scale 1600 width

hide empty members

namespace WConsole #EAFAF1 {

abstract class IGrid
abstract class IHeader
abstract class IPrecisionP1
abstract class IPrecisionP2
abstract class IRange
abstract class IWConsole
class Chart <<final>>
class Graph <<final>>
class Text <<final>>
class Font <<final>>

IWConsole    <|--- Chart
IHeader      <|--- Chart
IPrecisionP1 <|--- Chart
IRange       <|--- Chart
IGrid        <|--- Chart

IWConsole    <|--- Graph
IHeader      <|--- Graph
IPrecisionP2 <|--- Graph
IRange       <|--- Graph
IGrid        <|--- Graph

IWConsole    <|--- Text
Font         <-* Text

}

@enduml
```
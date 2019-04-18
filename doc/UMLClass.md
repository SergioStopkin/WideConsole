```plantuml
@startuml

scale 2000 width

hide empty members

namespace WConsole #EAFAF1 {

abstract class IGrid
abstract class IHeader
abstract class IPrecisionP1
abstract class IPrecisionP2
abstract class IPrint
abstract class IRange
abstract class IWConsole
class Chart
class Graph
class Text

IPrint <|-- IHeader
IPrint <|-- IWConsole

IWConsole    <|--- Chart
IHeader      <|--- Chart
IPrecisionP1 <|---  Chart
IRange       <|---  Chart
IGrid        <|---  Chart

IWConsole    <|--- Graph
IHeader      <|--- Graph
IPrecisionP2 <|---  Graph
IRange       <|---  Graph
IGrid        <|---  Graph

IWConsole <|--- Text

}

@enduml
```
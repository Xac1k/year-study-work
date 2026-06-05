
Классы и структуры архитектуры.
```mermaid
classDiagram
    class IContext {
        <<interface>>
        +~IContext()
    }
    
    class IFitnessContext {
        <<interface>>
    }
    
    class IEnergyContext {
        <<interface>>
    }
    
    class ILimitationsContext {
        <<interface>>
    }
    class ITFitness~ContextT~ {
        <<interface>>
        +Fitness(context) const* double
        #m_cacheFitness optional~double~
        +InvalidateCache()*
    }
    
    class ITEnergy~ContextT~ {
        <<interface>>
        +ComputeEnergy(context) const* double
    }
    class TEntityBase~N~ {
        #m_components array~double N~
        +TEntityBase()
        +TEntityBase(values array~double N~)
        +GetComponents() array~double N~
        +operator[](i) double
        +operator-(other) TEntityBase
        +operator+(other) TEntityBase
        +operator*(scalar) TEntityBase
        +operator/(divisor) TEntityBase
        +Abs() TEntityBase
        +MultiplyByArray(arr) TEntityBase
        +Dot(other) double
        +Norm() double
    }
    class ITEntity~N FitnessCtx EnergyCtx~ {
        <<interface>>
    }
    class ITGenerationStrategy~N CtxGenLimitations CtxFitness CtxEnergy~ {
        <<interface>>
        +Generate(ctx) unique_ptr~ITEntity~*
    }
    class ITEntityFactory~N CtxGenLimitations CtxFitness CtxEnergy~ {
        -m_population vector~unique_ptr~IEntityType~~
        -m_strategy unique_ptr~GeneratorType~
        +CreatePopulation(populationSize  ctx)
        +SetStrategy(strategy)
        +GetPopulation() vector~unique_ptr~IEntityType~~&
        +GetPopulationCopy() vector~unique_ptr~IEntityType~~
        +SearchBest_n(n  ctx  order) vector~unique_ptr~IEntityType~~
        +GetStatistics(ctx) PopulationStats
        +Clear()
        +Size() size_t
        +IsEmpty() bool
    }
    class PopulationStats {
        <<struct>>
        +minFitness double
        +maxFitness double
        +avgFitness double
        +stdDev double
    }
    
    class SortOption {
        <<enumeration>>
        ASC
        DESC
    }
    IContext <|-- IFitnessContext
    IContext <|-- IEnergyContext
    IContext <|-- ILimitationsContext
    
    TEntityBase <|-- ITEntity : множественное наследование
    ITFitness <|-- ITEntity
    ITEnergy <|-- ITEntity
    ITEntityFactory --> ITGenerationStrategy : uses
    ITEntityFactory --> ITEntity : manages
    ITEntityFactory --> PopulationStats : returns
    ITEntityFactory --> SortOption : uses
    
    ITGenerationStrategy --> ITEntity : creates
    
    ITFitness --> IFitnessContext : uses
    ITEnergy --> IEnergyContext : uses
    ITGenerationStrategy --> ILimitationsContext : uses
    ITEntityFactory --> ILimitationsContext : uses
    ITEntityFactory --> IFitnessContext : uses
    note for ITEntity "Абстрактный класс
    Объединяет TEntityBase 
    ITFitness и ITEnergy"
    note for ITEntityFactory "Главный класс для
    управления популяцией 
    в генетическом алгоритме"
    note for ITGenerationStrategy "Стратегия генерации
    новых особей"
    note for TEntityBase "Хранит компоненты
    и базовые векторные операции"
```

Общая файловая структура проекта разделение на клиентскую часть и часть за кадром
```mermaid
flowchart TB
    subgraph Core
        ContextH[Context.h<br/>IContext]
    end
    
    subgraph Entities
        GJOEntityH[GJOEntity.h<br/>ITEntity  TEntityBase<br/>ITFitness  ITEnergy]
        GJOEntityGeneratorH[GJOEntityGenerator.h<br/>ITGenerationStrategy]
    end
    
    subgraph Factory
        EntityFactoryH[EntityFactory.h<br/>ITEntityFactory]
    end
    
    subgraph Client
        Main[Main.cpp<br/>Usage Example]
    end
    
    ContextH --> Entities
    Entities --> Factory
    Factory --> Client
    
    Main -->|creates| Factory
    Main -->|implements| StrategyImpl[Concrete Strategy<br/>implements ITGenerationStrategy]
    Main -->|implements| EntityImpl[Concrete Entity<br/>implements ITEntity]
```

# Request Example
- POST http://localhost:8081/api/v1/compute
```json
{
  "dependencyContainer": {
    "estimator": {
      "coefficients": {
        "ThreatAvoidance": 1,
        "PathMinimizing": 0.2,
        "VarianceMinimizing": 0.2,
        "SmoothMaximizing": 0.2,
        "ThreatImportance": 0.2
      }
    },
    "updater": {
      "initialEnergy": 1.5,
      "maxIterations": 1000
    },
    "generator": {
      "limitationsX": {
        "min": 0,
        "max": 10
      },
      "limitationsY": {
        "min": 0,
        "max": 10
      },
      "limitationsZ": {
        "min": 0,
        "max": 10
      },
      "countWayPoints": 10,
      "maxGenerationIterations": 5
    }
  },
  "threats": [
    {
      "type": "airdefense",
      "center": {
        "x": 10,
        "y": 10,
        "z": 10
      },
      "radius": 10,
      "height": 10
    }
  ]
}
```
// Fill out your copyright notice in the Description page of Project Settings.


#include "GridNav.h"
#include "Node.h"

AGridNav::AGridNav()
{
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>("root");
}

void AGridNav::BeginPlay()
{
	Super::BeginPlay();
}

void AGridNav::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebug();
}

void AGridNav::Generate()
{
    nodes.Empty();

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            FVector _pos = FVector(x * gap, y * gap, 0 ) + GetActorLocation();
            
            UNodeNav* _node = NewObject<UNodeNav>();
            _node->InitNode(this, _pos);
            nodes.Add(_node);
        }
    }
    SetSuccessors();
}

void AGridNav::SetSuccessors()
{
    for (int i = 0; i < size * size; i++)
    {
        if (!nodes[i])
            continue;


        bool _canRight = i % size != size - 1,
            _canTop = i >= size,
            _canDown = i < (size * size) - size,
            _canLeft = i % size != 0;
        if (_canRight)
            nodes[i]->AddSuccessor(i + 1);
        if (_canLeft)
            nodes[i]->AddSuccessor(i - 1);
        if (_canTop)
        {
            nodes[i]->AddSuccessor(i - size);
            if (_canRight)
                nodes[i]->AddSuccessor((i + 1 - size));
            if (_canLeft)
                nodes[i]->AddSuccessor((i - 1 - size));
        }
        if (_canDown)
        {
            nodes[i]->AddSuccessor(i + size);
            if (_canRight)
                nodes[i]->AddSuccessor((i + 1 + size));
            if (_canLeft)
                nodes[i]->AddSuccessor((i - 1 + size));
        }
    }
}

void AGridNav::DrawDebug()
{
    if (nodes.Num() == 0)
        return;



    for (int i = 0; i < nodes.Num(); i++)
    {
        if (!nodes[i])
            continue;

        DrawDebugBox(GetWorld(), nodes[i]->GetPosition(), FVector(25), nodeColor, false, -1, 0, 2.0f);

        TArray<int> _successors = nodes[i]->GetSuccessors();

        for (size_t j = 0; j < _successors.Num(); j++)
        {
            DrawDebugLine(GetWorld(), nodes[i]->GetPosition(), nodes[_successors[j]]->GetPosition(), linesColor, false, -1, 0, 2.0f);
        }

        //nodes[i]->DrawDebug(nodeColor, linesColor);
    }
}


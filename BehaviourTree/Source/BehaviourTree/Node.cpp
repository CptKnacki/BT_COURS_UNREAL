

#include "Node.h"
#include "GridNav.h"
#include <Kismet/KismetSystemLibrary.h>

void UNodeNav::InitNode(TObjectPtr<AGridNav> _grid, FVector _position)
{
	grid = _grid;
	position = _position;
}

void UNodeNav::AddSuccessor(int _successor)
{
	successors.Add(_successor);
}

void UNodeNav::DrawDebug(FColor _nodeColor, FColor _lineColor)
{


	if (!grid)
		return;

	for (size_t i = 0; i < successors.Num(); i++)
	{
		if (!grid->GetNodes()[i])
			continue;

		UKismetSystemLibrary::PrintString(this, "YES");
		DrawDebugLine(GetWorld(), position, grid->GetNodes()[i]->position, _lineColor, false, -1, 0, 2.0f);
	}
}

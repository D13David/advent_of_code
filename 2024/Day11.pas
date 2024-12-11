unit Day11;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Math;

type
  TPairInt64 = array of Int64;

  TCacheItem = class
  private
    FValue: Int64;
    FCount: Int64;
  public
    constructor Create(value, count: Int64);
    property Value: Int64 read FValue;
    property Count: Int64 read FCount write FCount;
  end;

  TForm1 = class(TForm)
    lblResult: TLabel;
    procedure FormCreate(Sender: TObject);
  private
    procedure FindOrCreateItem(Cache: TList; Value, Count: Int64);
    procedure ClearCache(Cache: TList);
  public
    { Public declarations }
  end;

const
  Part = 2;

var
  Form1: TForm1;

implementation

{$R *.dfm}

constructor TCacheItem.Create(value, count: Int64);
begin
  inherited Create;
  FValue := value;
  FCount := count;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  Caches: array[0..1] of TList;
  CacheCurr, CachePrev: ^TList;
  CacheIndex: Integer;
  Item : TCacheItem;
  i, j, Blink, NumBlinks, Digits, NumNewValues : Integer;
  Count, Divident : Int64;
  NewValues : array [1..2] of Int64;
begin
  Caches[0] := TList.Create;
  Caches[1] := TList.Create;
  CacheIndex := 0;

  { we use these to swap the caches back and forth }
  CachePrev := @Caches[CacheIndex+0];
  CacheCurr := @Caches[CacheIndex+1];

  { initialize cache with puzzle values}
  CachePrev.Add(TCacheItem.Create(6,1));
  CachePrev.Add(TCacheItem.Create(11,1));
  CachePrev.Add(TCacheItem.Create(33023,1));
  CachePrev.Add(TCacheItem.Create(4134,1));
  CachePrev.Add(TCacheItem.Create(564,1));
  CachePrev.Add(TCacheItem.Create(0,1));
  CachePrev.Add(TCacheItem.Create(8922422,1));
  CachePrev.Add(TCacheItem.Create(688775,1));

  if Part = 1 then
    NumBlinks := 25
  else
    NumBlinks := 75;

  for Blink := 0 to NumBlinks-1 do begin
    for i := 0 to CachePrev.Count-1 do begin
      Item := CachePrev^[i];

      { calculate the next blink iteration for the current value}
      NumNewValues := 1;
      if Item.Value = 0 then
        NewValues[1] := 1
      else begin
        Digits := Trunc(Log10(Abs(Item.Value))) + 1;
        if (Digits mod 2) = 0 then begin
          Divident := Trunc(Power(10, Digits / 2));
          NewValues[1] := Trunc(Item.Value / Divident);
          NewValues[2] := Item.Value mod Divident;
          NumNewValues := 2;
        end
        else begin
          NewValues[1] := Item.Value * 2024;
        end;
      end;

      { update the value counters in cache }
      for j := 1 to NumNewValues do begin
        FindOrCreateItem(CacheCurr^, NewValues[j], Item.Count);
      end;
    end;
    
    { clear up previous cache }
    ClearCache(CachePrev^);

    { and swap caches }
    CacheIndex := 1 - CacheIndex;
    CachePrev := @Caches[(CacheIndex+0) mod 2];
    CacheCurr := @Caches[(CacheIndex+1) mod 2];
  end;

  Count := 0;
  for i := 0 to CachePrev.Count-1 do begin
    Item := CachePrev^[i];
    Count := Count + Item.Count;
  end;
  lblResult.Caption := IntToStr(Count);

  ClearCache(CachePrev^);
  Caches[0].Free; Caches[1].Free;
end;

procedure TForm1.FindOrCreateItem(Cache: TList; Value, Count: Int64);
var
  i: Integer;
  Item: TCacheItem;
begin
  for i := 0 to Cache.Count-1 do begin
    Item := Cache[i];
    if Item.Value = Value then begin
      Item.Count := Item.Count + Count;
      Exit;
    end;
  end;

  Cache.Add(TCacheItem.Create(Value, Count))
end;

procedure TForm1.ClearCache(Cache: TList);
var
  i: Integer;
begin
  for i := 0 to Cache.Count-1 do begin
    TCacheItem(Cache[i]).Free;
  end;
  Cache.Clear;
end;

end.

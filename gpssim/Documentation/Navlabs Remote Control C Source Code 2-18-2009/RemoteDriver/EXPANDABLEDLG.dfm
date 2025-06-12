object ExpandableDialog: TExpandableDialog
  Left = 712
  Top = 370
  BorderStyle = bsDialog
  Caption = 'ExpandableDialog'
  ClientHeight = 381
  ClientWidth = 572
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 120
  TextHeight = 16
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 572
    Height = 167
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object OKBtn: TButton
      Left = 464
      Top = 16
      Width = 75
      Height = 25
      Cancel = True
      Caption = 'OK'
      Default = True
      ModalResult = 1
      TabOrder = 0
    end
    object DetailsBtn: TButton
      Left = 464
      Top = 72
      Width = 75
      Height = 25
      Caption = 'Details >>'
      TabOrder = 1
      OnClick = DetailsBtnClick
    end
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 168
    Width = 572
    Height = 213
    BevelOuter = bvNone
    TabOrder = 1
    object LeftPanel: TPanel
      Left = 0
      Top = 0
      Width = 0
      Height = 213
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 0
    end
    object RightPanel: TPanel
      Left = 572
      Top = 0
      Width = 0
      Height = 213
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 1
    end
  end
end

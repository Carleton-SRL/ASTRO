object SetSvidFrame: TSetSvidFrame
  Left = 0
  Top = 0
  Width = 613
  Height = 562
  TabOrder = 0
  OnResize = FrameResize
  object OvcLabel2: TOvcLabel
    Left = 0
    Top = 0
    Width = 613
    Height = 57
    Align = alTop
    Alignment = taCenter
    Caption = 'Set SVID'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -37
    Font.Name = 'Times New Roman'
    Font.Style = [fsUnderline]
    ParentFont = False
  end
  object NumChanPnl: TRzPanel
    Left = 0
    Top = 57
    Width = 613
    Height = 64
    Align = alTop
    BorderOuter = fsNone
    TabOrder = 0
    object OvcLabel1: TOvcLabel
      Left = 112
      Top = 13
      Width = 286
      Height = 35
      Alignment = taRightJustify
      Caption = 'Enter Number of Channels:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -23
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object NumChansEdt: TRzSpinEdit
      Left = 408
      Top = 18
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 1
      TabOrder = 0
      OnChange = NumChansEdtChange
    end
  end
  object LeftPnl: TRzPanel
    Left = 0
    Top = 121
    Width = 273
    Height = 441
    Align = alLeft
    BorderOuter = fsNone
    TabOrder = 1
    object OvcLabel3: TOvcLabel
      Left = 11
      Top = 13
      Width = 80
      Height = 35
      Alignment = taCenter
      Caption = 'Chan'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -23
      Font.Name = 'Times New Roman'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object OvcLabel4: TOvcLabel
      Left = 115
      Top = 13
      Width = 80
      Height = 35
      Alignment = taCenter
      Caption = 'Svid'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -23
      Font.Name = 'Times New Roman'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object ChEdt0: TRzSpinEdit
      Left = 26
      Top = 58
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 1
      TabOrder = 0
    end
    object SvidEdt0: TRzSpinEdit
      Left = 130
      Top = 58
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 1
    end
    object ChEdt1: TRzSpinEdit
      Left = 26
      Top = 90
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 2
      TabOrder = 2
    end
    object SvidEdt1: TRzSpinEdit
      Left = 130
      Top = 90
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 3
    end
    object ChEdt2: TRzSpinEdit
      Left = 26
      Top = 122
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 3
      TabOrder = 4
    end
    object SvidEdt2: TRzSpinEdit
      Left = 130
      Top = 122
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 5
    end
    object ChEdt3: TRzSpinEdit
      Left = 26
      Top = 154
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 4
      TabOrder = 6
    end
    object SvidEdt3: TRzSpinEdit
      Left = 130
      Top = 154
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 7
    end
    object ChEdt4: TRzSpinEdit
      Left = 26
      Top = 186
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 5
      TabOrder = 8
    end
    object SvidEdt4: TRzSpinEdit
      Left = 130
      Top = 186
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 9
    end
    object ChEdt5: TRzSpinEdit
      Left = 26
      Top = 218
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 6
      TabOrder = 10
    end
    object SvidEdt5: TRzSpinEdit
      Left = 130
      Top = 218
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = 1
      TabOrder = 11
    end
  end
  object ClientPnl: TRzPanel
    Left = 273
    Top = 121
    Width = 340
    Height = 441
    Align = alClient
    BorderOuter = fsNone
    TabOrder = 2
    object ChanLbl2: TOvcLabel
      Left = 27
      Top = 13
      Width = 80
      Height = 35
      Alignment = taCenter
      Caption = 'Chan'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -23
      Font.Name = 'Times New Roman'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object SvidLbl2: TOvcLabel
      Left = 131
      Top = 13
      Width = 80
      Height = 35
      Alignment = taCenter
      Caption = 'Svid'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -23
      Font.Name = 'Times New Roman'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object ChEdt6: TRzSpinEdit
      Left = 42
      Top = 58
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 7
      TabOrder = 0
    end
    object SvidEdt6: TRzSpinEdit
      Left = 146
      Top = 58
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 1
    end
    object ChEdt7: TRzSpinEdit
      Left = 42
      Top = 90
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 8
      TabOrder = 2
    end
    object SvidEdt7: TRzSpinEdit
      Left = 146
      Top = 90
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 3
    end
    object ChEdt8: TRzSpinEdit
      Left = 42
      Top = 122
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 9
      TabOrder = 4
    end
    object SvidEdt8: TRzSpinEdit
      Left = 146
      Top = 122
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 5
    end
    object ChEdt9: TRzSpinEdit
      Left = 42
      Top = 154
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 10
      TabOrder = 6
    end
    object SvidEdt9: TRzSpinEdit
      Left = 146
      Top = 154
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 7
    end
    object ChEdt10: TRzSpinEdit
      Left = 42
      Top = 186
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 11
      TabOrder = 8
    end
    object SvidEdt10: TRzSpinEdit
      Left = 146
      Top = 186
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 9
    end
    object ChEdt11: TRzSpinEdit
      Left = 42
      Top = 218
      Width = 47
      Height = 24
      Increment = 1
      Max = 12
      Min = 1
      PageSize = 10
      Value = 12
      TabOrder = 10
    end
    object SvidEdt11: TRzSpinEdit
      Left = 146
      Top = 218
      Width = 47
      Height = 24
      Increment = 1
      Max = 32
      Min = -1
      PageSize = 10
      Value = -1
      TabOrder = 11
    end
  end
end

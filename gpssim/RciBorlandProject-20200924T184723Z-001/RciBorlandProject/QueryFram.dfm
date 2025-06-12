object QueryFrame: TQueryFrame
  Left = 0
  Top = 0
  Width = 643
  Height = 467
  TabOrder = 0
  object OvcLabel2: TOvcLabel
    Left = 0
    Top = 0
    Width = 643
    Height = 57
    Align = alTop
    Alignment = taCenter
    Caption = 'Query'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -37
    Font.Name = 'Times New Roman'
    Font.Style = [fsUnderline]
    ParentFont = False
  end
  object OvcLabel1: TOvcLabel
    Left = 136
    Top = 91
    Width = 121
    Height = 35
    Alignment = taRightJustify
    Caption = 'Message:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -23
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object OvcLabel3: TOvcLabel
    Left = 80
    Top = 139
    Width = 177
    Height = 35
    Alignment = taRightJustify
    Caption = 'Query When:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -23
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object OvcLabel4: TOvcLabel
    Left = 80
    Top = 187
    Width = 177
    Height = 35
    Alignment = taRightJustify
    Caption = 'Interval (s):'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -23
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Messagecbox: TRzComboBox
    Left = 272
    Top = 96
    Width = 145
    Height = 24
    Style = csDropDownList
    ItemHeight = 16
    TabOrder = 0
    Text = 'SIMMODE'
    Items.Strings = (
      'SIMMODE'
      'CHANSTAT'
      'BITRESULTS'
      'SYSCFG')
    ItemIndex = 0
  end
  object QueryWhencbox: TRzComboBox
    Left = 272
    Top = 144
    Width = 145
    Height = 24
    Style = csDropDownList
    ItemHeight = 16
    TabOrder = 1
    Text = 'Off'
    OnChange = QueryWhencboxChange
    Items.Strings = (
      'Off'
      'Once'
      'On Change'
      'Rate')
    ItemIndex = 0
  end
  object IntervalEdt: TRzSpinEdit
    Left = 272
    Top = 192
    Width = 47
    Height = 24
    Increment = 1
    Max = 1000
    Min = 1
    PageSize = 10
    Value = 1
    TabOrder = 2
  end
end

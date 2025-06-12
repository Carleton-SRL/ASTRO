object InterfaceAcceptFrame: TInterfaceAcceptFrame
  Left = 0
  Top = 0
  Width = 539
  Height = 67
  TabOrder = 0
  object InterfaceAcceptPnl: TRzPanel
    Left = 0
    Top = 0
    Width = 539
    Height = 67
    Align = alClient
    BorderOuter = fsGroove
    TabOrder = 0
    object AcceptLbl: TOvcLabel
      Left = 16
      Top = 17
      Width = 249
      Height = 28
      Alignment = taRightJustify
      Caption = 'Accept Interface Parameters:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
    end
    object AcceptInterfaceBtn: TRzBitBtn
      Left = 288
      Top = 15
      Width = 105
      Height = 33
      Default = True
      ModalResult = 6
      Caption = 'Accept'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      TextStyle = tsRaised
      OnClick = AcceptInterfaceBtnClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00666666666666
        66666666666666666666666666666666666666666666666666666666AC666666
        66666666F86666666666666A22C666666666666F88866666666666A2222C6666
        666666F88888666666666A222222C66666666F888888866666666A22CA222C66
        66666F888F88886666666A2C66A222C666666F8866F8888666666AC6666A222C
        66666F86666F8888666666666666A222C66666666666F8888666666666666A22
        2C66666666666F8888666666666666A222C66666666666F8888666666666666A
        22C666666666666F8886666666666666A2C6666666666666F886666666666666
        6AC66666666666666F8666666666666666666666666666666666}
      NumGlyphs = 2
    end
    object CancelInterfaceBtn: TRzBitBtn
      Left = 408
      Top = 15
      Width = 105
      Height = 33
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      TextStyle = tsRaised
      OnClick = CancelInterfaceBtnClick
      Kind = bkCancel
    end
  end
  object InterfaceAcceptOptionsTimer: TTimer
    Enabled = False
    Interval = 500
    OnTimer = InterfaceAcceptOptionsTimerTimer
    Left = 8
    Top = 8
  end
end

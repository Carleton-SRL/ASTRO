object DataExtractionReqForm: TDataExtractionReqForm
  Left = 63
  Top = 84
  Width = 422
  Height = 312
  Caption = 'Data Extraction Request'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object TopPnl: TRzPanel
    Left = 0
    Top = 0
    Width = 414
    Height = 57
    Align = alTop
    BorderOuter = fsGroove
    TabOrder = 0
    object TitleLbl: TOvcLabel
      Left = 2
      Top = 2
      Width = 410
      Height = 53
      Align = alClient
      Alignment = taCenter
      Caption = 'Data Extraction Request'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -27
      Font.Name = 'Times New Roman'
      Font.Style = [fsUnderline]
    end
  end
  object BottomPnl: TRzPanel
    Left = 0
    Top = 240
    Width = 414
    Height = 45
    Align = alBottom
    BorderOuter = fsGroove
    TabOrder = 1
    object OkBtn: TRzBitBtn
      Left = 46
      Top = 6
      Width = 100
      Height = 33
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      TextStyle = tsRaised
      Kind = bkOK
    end
    object CancelBtn: TRzBitBtn
      Left = 256
      Top = 6
      Width = 100
      Height = 33
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      TextStyle = tsRaised
      Kind = bkCancel
    end
  end
  object MainPnl: TRzPanel
    Left = 0
    Top = 57
    Width = 414
    Height = 183
    Align = alClient
    BorderOuter = fsGroove
    TabOrder = 2
    object Enabledcb: TRzCheckBox
      Left = 80
      Top = 48
      Width = 249
      Height = 65
      Caption = 'Data Extraction Request Enabled'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      State = cbUnchecked
      TabOrder = 0
    end
  end
end

object OperationErrorForm: TOperationErrorForm
  Left = 391
  Top = 313
  Width = 788
  Height = 577
  Caption = 'Operation Error'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFF
    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8888
    FFFFFFFFFFF9999FFFFF888888FF887777888FFFFFF9999F888777887757FFFF
    88877778FFF999977788FFFFFFF8888888FFF887778999988FFFFFFFFFFFFFFF
    F88888FF875778FFFFFFFFFFFFFFFFFFFFFFFF877778777FFFFFFFFFFFFFFFFF
    FFFFFF887778F87577557788FFFFFFFFFFFF8788FF8999987778888777FFFFFF
    FFF8878F77899998F8778FFF877FFFFFFF787878FF79999778F8778FFF77FFFF
    F77878FFF54999944888F877FF888FF87777FFFF7449999445FF78F778F88787
    778FFFF844499994448FF87F8787F8557FFFFFF844499994447FFFF88F748774
    78FFFFF844499994447FFFFF8774F74F877FFFF844499994447FFFFFF8478487
    8F778FFF44499994448FFFFFF57888FF87F8778F8449999447FFFFFF74FF8FFF
    FF88F877884999947FFFFFF748FFFFFFFFFF78F877799998FFFFFF748FFFFFFF
    FFFFF878F879999FFFFFF778FFFF8FFFFFFFFFF878F999988FF8778FFFFF88FF
    FFFFFFFFF879999777577FFFFFFFF7FFFFFFFFFFFFF99998777777888888F778
    FFFFFFFFFFF88777778F88887777FF877778888777788F78788888FFFFFFFFFF
    F8887788FFFF8778FFFFF8888888FFFFFFFFFFFFFF8787FFFFFFFFFFFFFFFFFF
    FFFFFFFF87778FFFFFFFFFFFFFFFFFFFFFFFF877778FFFFFFFFFFFFFFFFF0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object BottomPnl: TRzPanel
    Left = 0
    Top = 509
    Width = 780
    Height = 41
    Align = alBottom
    BorderOuter = fsGroove
    TabOrder = 0
    object Buttons: TRzDialogButtons
      Left = 2
      Top = 2
      Width = 776
      Height = 37
      Align = alClient
      CaptionOk = 'Yes'
      CaptionCancel = 'No'
      CaptionHelp = '&Help'
      ShowGlyphs = True
      WidthOk = 200
      WidthCancel = 200
      OnClickOk = ButtonsClickOk
      OnClickCancel = ButtonsClickCancel
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
  end
  object TopClientPnl: TRzPanel
    Left = 0
    Top = 46
    Width = 780
    Height = 130
    Align = alTop
    BorderOuter = fsGroove
    TabOrder = 1
    object GeneralErrorLbl: TOvcLabel
      Left = 2
      Top = 2
      Width = 776
      Height = 126
      Align = alClient
      Alignment = taCenter
      Caption = 
        'There has been an error in the system initialization.  This erro' +
        'r may or may not render the simulation unrunnable.  Do you wish ' +
        'to attempt to run the simulation?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Times New Roman'
      Font.Style = []
    end
  end
  object TopPnl: TRzPanel
    Left = 0
    Top = 0
    Width = 780
    Height = 46
    Align = alTop
    BorderOuter = fsGroove
    TabOrder = 2
    object RzLabel1: TRzLabel
      Left = 2
      Top = 2
      Width = 776
      Height = 42
      Align = alClient
      Alignment = taCenter
      Caption = 'Operation Error'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -32
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsUnderline]
      ParentFont = False
      Blinking = True
      FrameSides = []
    end
  end
  object ClientPnl: TRzPanel
    Left = 0
    Top = 176
    Width = 780
    Height = 333
    Align = alClient
    BorderOuter = fsGroove
    TabOrder = 3
    object ErrorStrScrollBox: TScrollBox
      Left = 2
      Top = 2
      Width = 776
      Height = 329
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      TabOrder = 0
      object ErrorSpecificLbl: TOvcLabel
        Left = 0
        Top = 0
        Width = 772
        Height = 325
        Align = alClient
        Alignment = taCenter
        Caption = 'Error'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -27
        Font.Name = 'Times New Roman'
        Font.Style = []
      end
    end
  end
end

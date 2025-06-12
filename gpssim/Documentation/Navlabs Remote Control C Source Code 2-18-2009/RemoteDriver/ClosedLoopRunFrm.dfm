object ClosedLoopRunForm: TClosedLoopRunForm
  Left = 294
  Top = 108
  Width = 1399
  Height = 984
  Caption = 'Closed Loop Control'
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
    FFFFFFFFFFFFFFFFFFFF888888FF887777888FFFFFFFFFFF888777887757FFFF
    88877778FFFFF8877788FFFFFFF8888888FFF887778877788FFFFFFFFFFFFFFF
    F88888FF875778FFFFFFFFFFFFFFFFFFFFFFFF877778777FFFFFFFFFFFFFFFFF
    FFFFFF887778F87577557788FFFFFFFFFFFF8788FF8774887778888777FFFFFF
    FFF8878F778F8878F8778FFF877FFFFFFF787878FF74444778F8778FFF77FFFF
    F77878FFF54444444888F877FF888FF87777FFFF7444444445FF78F778F88787
    778FFFF844444444448FF87F8787F8557FFFFFF844444444447FFFF88F748774
    78FFFFF844444444447FFFFF8774F74F877FFFF844444444447FFFFFF8478487
    8F778FFF44444444448FFFFFF57888FF87F8778F8444444447FFFFFF74FF8FFF
    FF88F877884444447FFFFFF748FFFFFFFFFF78F877777778FFFFFF748FFFFFFF
    FFFFF878F87778FFFFFFF778FFFF8FFFFFFFFFF878F877788FF8778FFFFF88FF
    FFFFFFFFF878FF8777577FFFFFFFF7FFFFFFFFFFFFFF8788777777888888F778
    FFFFFFFFFFF88777778F88887777FF877778888777788F78788888FFFFFFFFFF
    F8887788FFFF8778FFFFF8888888FFFFFFFFFFFFFF8787FFFFFFFFFFFFFFFFFF
    FFFFFFFF87778FFFFFFFFFFFFFFFFFFFFFFFF877778FFFFFFFFFFFFFFFFF0000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  Menu = ClosedLoopMenu
  OldCreateOrder = False
  Position = poDesktopCenter
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object MainToolbar: TRzToolbar
    Left = 0
    Top = 0
    Width = 1391
    Height = 29
    BorderInner = fsNone
    BorderOuter = fsGroove
    BorderSides = [sdTop]
    BorderWidth = 0
    TabOrder = 0
    ToolbarControls = (
      BtnStop)
    object BtnStop: TRzToolbarButton
      Left = 4
      Top = 4
      Width = 21
      Height = 20
      Hint = 'Stop'
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        0400000000000001000000000000000000001000000010000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00666666666666
        6666666666666666666666666111116666666666688888666666666119999911
        6666666888888888666666199999999916666688888888888666619999999999
        916668888888888888666199FF999FF9916668886688866888661999FFF9FFF9
        9916888866686668888619999FFFFF9999168888866666888886199999FFF999
        9916888888666888888619999FFFFF99991688888666668888861999FFF9FFF9
        991688886668666888866199FF999FF991666888668886688866619999999999
        9166688888888888886666199999999916666688888888888666666119999911
        6666666888888888666666666111116666666666688888666666}
      NumGlyphs = 2
      OnClick = BtnStopClick
      HotNumGlyphs = 0
      IgnoreActionCaption = True
    end
  end
  object RzStatusBar1: TRzStatusBar
    Left = 0
    Top = 923
    Width = 1391
    Height = 15
    AutoStyle = False
    BorderInner = fsNone
    BorderOuter = fsNone
    BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
    BorderWidth = 0
    TabOrder = 1
  end
  object TopPnl: TRzSizePanel
    Left = 0
    Top = 29
    Width = 1391
    Height = 192
    Align = alTop
    TabOrder = 2
    UseGradients = True
    object TopSplitter: TRzSplitter
      Left = 0
      Top = 0
      Width = 1391
      Height = 187
      Position = 410
      Percent = 30
      RealTimeDrag = True
      UseGradients = True
      Align = alClient
      TabOrder = 0
      BarSize = (
        410
        0
        414
        187)
      UpperLeftControls = (
        RightTopPnl)
      LowerRightControls = (
        InterfaceStatusPnl)
      object RightTopPnl: TRzPanel
        Left = 0
        Top = 0
        Width = 410
        Height = 187
        Align = alClient
        BorderOuter = fsGroove
        TabOrder = 0
        object SimulationStatusTitlePnl: TRzPanel
          Left = 2
          Top = 2
          Width = 406
          Height = 47
          Align = alTop
          BorderOuter = fsGroove
          TabOrder = 0
          object SimulationStatusTitleLbl: TOvcLabel
            Left = 2
            Top = 2
            Width = 402
            Height = 43
            Align = alClient
            Alignment = taCenter
            Caption = 'Simulation Status'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -27
            Font.Name = 'Times New Roman'
            Font.Style = [fsUnderline]
          end
        end
        object SimulationStatusDisplayPnl: TRzPanel
          Left = 2
          Top = 49
          Width = 406
          Height = 136
          Align = alClient
          BorderOuter = fsGroove
          TabOrder = 1
          object OvcLabel4: TOvcLabel
            Left = 37
            Top = 28
            Width = 122
            Height = 20
            Alignment = taRightJustify
            Caption = 'Simulator Time:'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'Times New Roman'
            Font.Style = []
          end
          object SimulatorTimeLbl: TOvcLabel
            Left = 167
            Top = 28
            Width = 46
            Height = 20
            Caption = '0'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'Times New Roman'
            Font.Style = []
          end
          object LastMsgLbl: TOvcLabel
            Left = 167
            Top = 54
            Width = 200
            Height = 20
            Caption = '(none)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'Times New Roman'
            Font.Style = []
          end
          object OvcLabel10: TOvcLabel
            Left = 37
            Top = 54
            Width = 122
            Height = 20
            Alignment = taRightJustify
            Caption = 'Last Message:'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'Times New Roman'
            Font.Style = []
          end
          object StartSimBtn: TRzBitBtn
            Left = 56
            Top = 84
            Width = 257
            Height = 40
            Caption = 'Start Simulation'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            TextStyle = tsRaised
            OnClick = StartSimBtnClk
            Glyph.Data = {
              66090000424D660900000000000036000000280000001C0000001C0000000100
              18000000000030090000C30E0000C30E00000000000000000000FF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF378B6432A146378B64FF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FF39A94F31A64832A1462B9348FF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF378B6431A64831
              A64831A64831A6482B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FF378B6431A64831A64831A64831A64831A6482B
              9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF378B
              6432A64931A64831A64831A64831A64831A64831A6489DAE66FF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF378B6431A64831A64837B7552F8D
              5837B75531A64832A1462B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FF378B6431A64831A64837B7552F8D5833A3462F8D5831A64831A64831A6
              489DAE66FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF378B6432A64931A64831A648
              37B7552F8D58FF00FF2F8D5837B75531A64831A6482B9348FF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FF399B6132A14631A64831A64837B7552F8D58FF00FFFF00FFFF00FF
              2F8D5837B75531A64831A6482B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF399B6139C15631
              A64831A64837B7552F8D58FF00FFFF00FFFF00FFFF00FF2F8D5837B75531A648
              31A6482B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FF399B6139C15637B7552F8D58FF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FF2F8D5837B75532A14631A6489DAE66FF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FF399B612F8D58FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FF2F8D5837B75532A1462B9348FF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF2F8D5837
              B75531A6482B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF2F8D5837B75531A6482B9348FF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FF2F8D5837B75531A6482B9348FF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FF2F8D5837B75531A6482B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF31A64837B75531A6
              489DAE66FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FF2F8D5837B7552B9348FF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FF2F8D5837B7552B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF31A648
              37B7552B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF32A64931A6489DAE66FF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FF31A6482F8D589DAE66FF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FF2F8D582B9348FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
              00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
              FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
              FFFF00FFFF00FFFF00FF}
            Spacing = 3
          end
        end
      end
      object InterfaceStatusPnl: TRzPanel
        Left = 0
        Top = 0
        Width = 977
        Height = 187
        Align = alClient
        BorderOuter = fsGroove
        TabOrder = 0
        object InterfaceStatusDisplaySplitter: TRzSplitter
          Left = 2
          Top = 49
          Width = 973
          Height = 136
          Position = 442
          Percent = 46
          UseGradients = True
          Align = alClient
          TabOrder = 0
          BarSize = (
            442
            0
            446
            136)
          UpperLeftControls = (
            InterfaceLeftPnl)
          LowerRightControls = (
            InterfaceStatusDisplayPnl)
          object InterfaceLeftPnl: TRzPanel
            Left = 0
            Top = 0
            Width = 442
            Height = 136
            Align = alClient
            BorderOuter = fsGroove
            TabOrder = 0
            object OvcLabel1: TOvcLabel
              Left = 59
              Top = 28
              Width = 122
              Height = 20
              Alignment = taRightJustify
              Caption = 'Num Msgs Sent:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -15
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
            object OvcLabel2: TOvcLabel
              Left = 59
              Top = 54
              Width = 122
              Height = 20
              Alignment = taRightJustify
              Caption = 'Num Msgs Rcvd:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -15
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
            object NumMsgsSentLbl: TOvcLabel
              Left = 200
              Top = 28
              Width = 33
              Height = 20
              Caption = '0'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -15
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
            object NumMsgsRcvdLbl: TOvcLabel
              Left = 200
              Top = 54
              Width = 33
              Height = 20
              Caption = '0'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -15
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
            object OvcLabel5: TOvcLabel
              Left = 5
              Top = 80
              Width = 176
              Height = 20
              Alignment = taRightJustify
              Caption = 'Num Msgs Rcvd (Exc Stat):'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -15
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
            object NumMsgsRcvdExceptStatLbl: TOvcLabel
              Left = 200
              Top = 80
              Width = 33
              Height = 20
              Caption = '0'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clNavy
              Font.Height = -15
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
            object SendMsgBtn: TRzBitBtn
              Left = 264
              Top = 28
              Width = 105
              Height = 40
              Caption = 'Send Messages'
              TabOrder = 0
              TextStyle = tsRaised
              OnClick = SendMsgBtnClk
              Glyph.Data = {
                66090000424D660900000000000036000000280000001C0000001C0000000100
                18000000000030090000930B0000930B00000000000000000000FF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF8F7C67FF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FF8F7C67917A63FF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FF8F7C67D2A376917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF8F7C67DCA677D2A37691
                7A63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFA57F61E6AD7ADCA677DDA677917A63FF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF9B775A9B775AA27D5FAC8363
                B68A67B68A67B68A67B68A67B68A67B68A67B68A67B68A67B68A67C6956EC695
                6EEAAE7BE5AA79E9AC79DDA677917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FF9B775ACD9C70D8A274E0A777E9AC7AE9AC7AE9AC7AEEAF7C
                EEAF7CEEAF7CEEAF7CEEAF7CEEAF7CEEAF7CEBAD7BEEAF7CE9AD7BE9AC79E4A7
                77DBA475917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF9B775AE1
                A877E3A977E8AC79ECAE7AEFB07BF1B07CF2B07CF2B17CF2B17CF4B27DF5B37D
                F6B47EF9B57FF7B47EF2B27DEFAF7CE9AC79E4A777DBA475D39E71917A63FF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FF9B775ADEA475E1A675E7A977EBAB77ED
                AC76F0AB74F0AB74F0AB74F1AC75F2AD76F4AE76F4AF78F6B078F6B078F4B07A
                F1B07BECAC79E4A777DBA475D39E71C5956B917A63FF00FFFF00FFFF00FFFF00
                FFFF00FF9B775ADBA273DFA474E5A979EBB182F0BA8FF3C098F4C39BF4C39BF4
                C29AF5C198F5C095F5BF94F6BF94F6BD8FF4B686F0B07DEBAB79E4A776DBA475
                D9A072CA966BB68D67917A63FF00FFFF00FFFF00FFFF00FF987458D49D70D9A2
                74E1AA7EE9BB96F2D1B8F6E2D1F8E7D9F8E7D9F8E4D6F7E1D0F7DECBF7DCC7F8
                DECAF8DDC7F4CCACEDB589E6AA7AE0A474D9A072CA966BBE8F66917A63FF00FF
                FF00FFFF00FFFF00FFFF00FF8F6E54CD996DD19D73D9A67DE1B38DE7BD9CEAC2
                A4EAC3A5EBC4A5ECC6A7ECC6A9EEC8ACF0CDB2F5DAC5F9E7DAF5DECCEBBD99E0
                A87BD9A072CA966BC29268917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                8F6E54C3946BC7976ECD9C73D2A078D5A37AD6A47BD7A47BD8A57BD9A67CDAA7
                7EDCAA80DFAD85E5B691EAC2A2E9C2A3E1B28DD9A072CA966BCA986D917A63FF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFB18261A07B63A47C61A97E61
                A97E61B18261B18261B18261B18261B18261B18261B68B6BB68B6BB68B6BB68B
                6BD9A982D2A27ACA966BC7966D917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF8E7562CA9973C2946EBC8F68917A
                63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FF8E7562BC9574B18A69917A63FF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF8E7562B08D70
                917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FF8E7562917A63FF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FF917A63FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
                00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
                FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
                FFFF00FFFF00FFFF00FF}
              Spacing = 3
            end
            object SendTrajBtn: TRzBitBtn
              Left = 288
              Top = 88
              Caption = 'Send 1 Traj'
              TabOrder = 1
              OnClick = SendTrajBtnClick
            end
          end
          object InterfaceStatusDisplayPnl: TRzPanel
            Left = 0
            Top = 0
            Width = 527
            Height = 136
            Align = alClient
            BorderOuter = fsGroove
            TabOrder = 0
            object InterfaceStatusStrLbl: TOvcLabel
              Left = 2
              Top = 2
              Width = 523
              Height = 132
              Align = alClient
              Caption = '(Interface Status Unknown)'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -19
              Font.Name = 'Times New Roman'
              Font.Style = []
            end
          end
        end
        object InterfaceStatusDisplayTitlePnl: TRzPanel
          Left = 2
          Top = 2
          Width = 973
          Height = 47
          Align = alTop
          BorderOuter = fsGroove
          TabOrder = 1
          object InterfaceStatusDisplayTitleLbl: TOvcLabel
            Left = 2
            Top = 2
            Width = 969
            Height = 43
            Align = alClient
            Alignment = taCenter
            Caption = 'Interface Status'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -27
            Font.Name = 'Times New Roman'
            Font.Style = [fsUnderline]
          end
        end
      end
    end
  end
  object MainClientPnl: TRzPanel
    Left = 0
    Top = 221
    Width = 1391
    Height = 702
    Align = alClient
    BorderOuter = fsGroove
    TabOrder = 3
    object LeftMainPnl: TRzSizePanel
      Left = 2
      Top = 2
      Width = 211
      Height = 698
      TabOrder = 0
      UseGradients = True
      inline MsgListFrame: TMsgListFrame
        Left = 0
        Top = 0
        Width = 206
        Height = 698
        Align = alClient
        TabOrder = 0
        inherited TopPnl: TRzPanel
          Width = 206
        end
        inherited MsgListBox: TRzTabbedListBox
          Width = 206
          Height = 638
          TabStops.Min = -2147483647
          TabStops.Max = 2147483647
        end
        inherited MsgListsb: TStatusBar
          Top = 679
          Width = 206
        end
      end
    end
    object RightMainPnl: TRzPanel
      Left = 213
      Top = 2
      Width = 1176
      Height = 698
      Align = alClient
      BorderOuter = fsNone
      TabOrder = 1
      object MainPageCtrl: TPageControl
        Left = 0
        Top = 0
        Width = 1176
        Height = 698
        ActivePage = VehSheet
        Align = alClient
        TabIndex = 0
        TabOrder = 0
        TabPosition = tpBottom
        object VehSheet: TTabSheet
          Caption = 'Vehicle'
          object GtChart: TChart
            Left = 0
            Top = 0
            Width = 1168
            Height = 672
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            Legend.Visible = False
            MarginBottom = 5
            MarginLeft = 5
            MarginRight = 5
            MarginTop = 5
            Title.Font.Color = clBlack
            Title.Font.Height = -20
            Title.Text.Strings = (
              'Ground Track')
            BottomAxis.Axis.Visible = False
            BottomAxis.MinorTickCount = 2
            BottomAxis.StartPosition = 3
            BottomAxis.EndPosition = 97
            BottomAxis.Title.Caption = 'Longitude'
            BottomAxis.Title.Font.Height = -17
            LeftAxis.Axis.Visible = False
            LeftAxis.LabelsAngle = 90
            LeftAxis.StartPosition = 3
            LeftAxis.EndPosition = 97
            LeftAxis.Title.Caption = 'Latitude'
            LeftAxis.Title.Font.Height = -17
            RightAxis.Axis.Visible = False
            RightAxis.StartPosition = 3
            RightAxis.EndPosition = 97
            TopAxis.Axis.Visible = False
            TopAxis.StartPosition = 3
            TopAxis.EndPosition = 97
            View3D = False
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 0
          end
        end
        object SatSheet: TTabSheet
          Caption = 'SV Data'
          ImageIndex = 1
          object MainRightSizePnl: TRzSizePanel
            Left = 877
            Top = 0
            Width = 291
            Height = 672
            Align = alRight
            TabOrder = 0
            UseGradients = True
            object DataExtractionPnl: TRzPanel
              Left = 5
              Top = 0
              Width = 286
              Height = 672
              Align = alClient
              BorderOuter = fsGroove
              TabOrder = 0
              object DataTopPnl: TRzPanel
                Left = 2
                Top = 2
                Width = 282
                Height = 44
                Align = alTop
                BorderOuter = fsGroove
                TabOrder = 0
                object DataExtractionTitleLbl: TOvcLabel
                  Left = 2
                  Top = 2
                  Width = 278
                  Height = 40
                  Align = alClient
                  Alignment = taCenter
                  Caption = 'Data Extraction'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clBlack
                  Font.Height = -27
                  Font.Name = 'Times New Roman'
                  Font.Style = [fsUnderline]
                end
              end
              object DataExtractionHeaderPnl: TRzPanel
                Left = 2
                Top = 46
                Width = 282
                Height = 52
                Align = alTop
                BorderOuter = fsGroove
                TabOrder = 1
                object OvcLabel7: TOvcLabel
                  Left = 13
                  Top = 6
                  Width = 137
                  Height = 20
                  Alignment = taRightJustify
                  Caption = 'Time of Applicability:'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clBlack
                  Font.Height = -15
                  Font.Name = 'Times New Roman'
                  Font.Style = []
                end
                object DataExtractionTimeLbl: TOvcLabel
                  Left = 156
                  Top = 6
                  Width = 59
                  Height = 20
                  Caption = '604799'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clNavy
                  Font.Height = -15
                  Font.Name = 'Times New Roman'
                  Font.Style = []
                end
                object ChanLbl: TOvcLabel
                  Left = 13
                  Top = 26
                  Width = 27
                  Height = 20
                  Alignment = taCenter
                  Caption = 'Ch'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clBlack
                  Font.Height = -16
                  Font.Name = 'Times New Roman'
                  Font.Style = [fsUnderline]
                end
                object OvcLabel8: TOvcLabel
                  Left = 46
                  Top = 25
                  Width = 46
                  Height = 21
                  Alignment = taCenter
                  Caption = 'Svid'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clBlack
                  Font.Height = -16
                  Font.Name = 'Times New Roman'
                  Font.Style = [fsUnderline]
                end
                object OvcLabel9: TOvcLabel
                  Left = 143
                  Top = 25
                  Width = 53
                  Height = 21
                  Alignment = taCenter
                  Caption = 'Range'
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clBlack
                  Font.Height = -16
                  Font.Name = 'Times New Roman'
                  Font.Style = [fsUnderline]
                end
              end
              object DataExtractionScrollBox: TScrollBox
                Left = 2
                Top = 98
                Width = 282
                Height = 572
                Align = alClient
                TabOrder = 2
              end
            end
          end
          object SvLookAnglePnl: TRzPanel
            Left = 0
            Top = 0
            Width = 877
            Height = 672
            Align = alClient
            BorderOuter = fsGroove
            TabOrder = 1
            object SatelliteChart: TChart
              Left = 2
              Top = 2
              Width = 873
              Height = 668
              AllowPanning = pmNone
              BackWall.Brush.Color = clWhite
              BackWall.Brush.Style = bsClear
              BackWall.Pen.Visible = False
              Legend.DividingLines.Visible = True
              Legend.LegendStyle = lsValues
              Legend.TextStyle = ltsPlain
              MarginBottom = 10
              MarginLeft = 10
              MarginRight = 10
              MarginTop = 10
              Title.Font.Color = clBlack
              Title.Font.Height = -20
              Title.Font.Style = [fsUnderline]
              Title.Text.Strings = (
                ' Satellite Visibility ')
              AxisVisible = False
              BottomAxis.Automatic = False
              BottomAxis.AutomaticMaximum = False
              BottomAxis.AutomaticMinimum = False
              BottomAxis.Increment = 10
              BottomAxis.Inverted = True
              BottomAxis.Maximum = 90
              BottomAxis.Visible = False
              ClipPoints = False
              Frame.Visible = False
              LeftAxis.Automatic = False
              LeftAxis.AutomaticMaximum = False
              LeftAxis.AutomaticMinimum = False
              LeftAxis.ExactDateTime = False
              LeftAxis.Increment = 10
              LeftAxis.Maximum = 90
              LeftAxis.Visible = False
              RightAxis.Automatic = False
              RightAxis.AutomaticMaximum = False
              RightAxis.AutomaticMinimum = False
              RightAxis.ExactDateTime = False
              RightAxis.Increment = 10
              RightAxis.Inverted = True
              RightAxis.Maximum = 90
              RightAxis.Visible = False
              TopAxis.Automatic = False
              TopAxis.AutomaticMaximum = False
              TopAxis.AutomaticMinimum = False
              TopAxis.Maximum = 90
              TopAxis.Visible = False
              View3D = False
              View3DOptions.Elevation = 315
              View3DOptions.Orthogonal = False
              View3DOptions.Perspective = 0
              View3DOptions.Rotation = 360
              View3DWalls = False
              Zoom.Allow = False
              Align = alClient
              TabOrder = 0
              PrintMargins = (
                31
                15
                31
                15)
              object SatelliteSeries: TPolarSeries
                Marks.Callout.Brush.Color = clBlack
                Marks.Visible = True
                Title = 'SatelliteSeries'
                Circled = True
                AngleIncrement = 10
                AngleValues.Name = 'Angle'
                AngleValues.Order = loAscending
                Brush.Color = clWhite
                Brush.Style = bsClear
                CircleLabels = True
                CirclePen.Color = clSilver
                CirclePen.Visible = False
                ClockWiseLabels = True
                CloseCircle = False
                Pen.Color = clBlue
                Pen.Visible = False
                Pointer.InflateMargins = True
                Pointer.Style = psRectangle
                Pointer.Visible = False
                RadiusIncrement = 10
                RotationAngle = 90
              end
            end
          end
        end
      end
    end
  end
  object ClosedLoopMenu: TMainMenu
    Left = 1176
    object Options: TMenuItem
      Caption = 'Option'
      object DispOptionsMenu: TMenuItem
        Caption = 'Display'
      end
    end
    object HelpMenu: TMenuItem
      Caption = 'Help'
      object AboutMenu: TMenuItem
        Caption = 'About'
        OnClick = AboutMenuClick
      end
    end
  end
  object CLCTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = CLCTimerTimer
    Left = 1233
    Top = 65533
  end
end

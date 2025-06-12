object RciRunForm: TRciRunForm
  Left = 243
  Top = 128
  Width = 1260
  Height = 1026
  Caption = 'Remote Control Interface Run...'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
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
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 16
  object TopSizePnl: TRzSizePanel
    Left = 0
    Top = 0
    Width = 1252
    Height = 272
    Align = alTop
    TabOrder = 0
    object SimMsgsPageCtrl: TPageControl
      Left = 0
      Top = 0
      Width = 1252
      Height = 267
      ActivePage = AckSheet
      Align = alClient
      Style = tsFlatButtons
      TabOrder = 0
      object AckSheet: TTabSheet
        Caption = 'Ack'
        object RzSizePanel1: TRzSizePanel
          Left = 0
          Top = 0
          Width = 561
          Height = 233
          TabOrder = 0
          object RzPanel4: TRzPanel
            Left = 0
            Top = 0
            Width = 556
            Height = 233
            Align = alClient
            TabOrder = 0
            object OvcLabel3: TOvcLabel
              Left = 2
              Top = 2
              Width = 552
              Height = 35
              Align = alTop
              Alignment = taCenter
              Caption = 'Acknowledge'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -23
              Font.Name = 'Times New Roman'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
            object OvcLabel4: TOvcLabel
              Left = 32
              Top = 48
              Width = 145
              Height = 35
              Alignment = taRightJustify
              Caption = 'Time Rcvd:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object AckTimeRcvdLbl: TOvcLabel
              Left = 184
              Top = 48
              Width = 145
              Height = 25
              Appearance = apSunken
              Caption = '0'
              ColorScheme = csCustom
              CustomSettings.HighlightDirection = sdDownRight
              CustomSettings.ShadowDirection = sdUpLeft
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlue
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object AckMsgValidLbl: TOvcLabel
              Left = 184
              Top = 120
              Width = 145
              Height = 25
              Appearance = apSunken
              Caption = '(none)'
              ColorScheme = csCustom
              CustomSettings.HighlightDirection = sdDownRight
              CustomSettings.ShadowDirection = sdUpLeft
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlue
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object AckMsgIdLbl: TOvcLabel
              Left = 184
              Top = 88
              Width = 145
              Height = 25
              Appearance = apSunken
              Caption = '(none)'
              ColorScheme = csCustom
              CustomSettings.HighlightDirection = sdDownRight
              CustomSettings.ShadowDirection = sdUpLeft
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlue
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object AckSimModeValidLbl: TOvcLabel
              Left = 184
              Top = 152
              Width = 145
              Height = 25
              Appearance = apSunken
              Caption = '(none)'
              ColorScheme = csCustom
              CustomSettings.HighlightDirection = sdDownRight
              CustomSettings.ShadowDirection = sdUpLeft
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlue
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object OvcLabel23: TOvcLabel
              Left = 32
              Top = 88
              Width = 145
              Height = 35
              Alignment = taRightJustify
              Caption = 'Acked Msg:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object OvcLabel24: TOvcLabel
              Left = 32
              Top = 120
              Width = 145
              Height = 35
              Alignment = taRightJustify
              Caption = 'Msg Valid:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
            object OvcLabel25: TOvcLabel
              Left = 32
              Top = 152
              Width = 145
              Height = 35
              Alignment = taRightJustify
              Caption = 'Sim Mode Valid:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -20
              Font.Name = 'Times New Roman'
              Font.Style = []
              ParentFont = False
            end
          end
        end
        object AckRightPnl: TRzPanel
          Left = 561
          Top = 0
          Width = 683
          Height = 233
          Align = alClient
          TabOrder = 1
          object AckListBox: TRzTabbedListBox
            Left = 2
            Top = 2
            Width = 679
            Height = 229
            TabStops.Min = -2147483647
            TabStops.Max = 2147483647
            TabStops.Integers = (
              8)
            Align = alClient
            Color = clBtnFace
            ItemHeight = 16
            TabOrder = 0
          end
        end
      end
      object ChanStatSheet: TTabSheet
        Caption = 'Channel Status'
        ImageIndex = 1
        object OvcLabel5: TOvcLabel
          Left = 0
          Top = 0
          Width = 1244
          Height = 35
          Align = alTop
          Alignment = taCenter
          Caption = 'Channel Status'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = [fsUnderline]
          ParentFont = False
        end
        object OvcLabel6: TOvcLabel
          Left = 16
          Top = 48
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Chan:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel7: TOvcLabel
          Left = 16
          Top = 96
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Svid:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel8: TOvcLabel
          Left = 16
          Top = 152
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Power:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh0: TOvcLabel
          Left = 120
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh1: TOvcLabel
          Left = 168
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh2: TOvcLabel
          Left = 216
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh3: TOvcLabel
          Left = 264
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh4: TOvcLabel
          Left = 312
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh5: TOvcLabel
          Left = 360
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh6: TOvcLabel
          Left = 408
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh7: TOvcLabel
          Left = 456
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh8: TOvcLabel
          Left = 504
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh9: TOvcLabel
          Left = 552
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh10: TOvcLabel
          Left = 600
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh11: TOvcLabel
          Left = 648
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh12: TOvcLabel
          Left = 696
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatCh13: TOvcLabel
          Left = 744
          Top = 48
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl0: TOvcLabel
          Left = 120
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl1: TOvcLabel
          Left = 168
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl2: TOvcLabel
          Left = 216
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl3: TOvcLabel
          Left = 264
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl4: TOvcLabel
          Left = 312
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl5: TOvcLabel
          Left = 360
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl6: TOvcLabel
          Left = 408
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl7: TOvcLabel
          Left = 456
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl8: TOvcLabel
          Left = 504
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl9: TOvcLabel
          Left = 552
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl10: TOvcLabel
          Left = 600
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl11: TOvcLabel
          Left = 648
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl12: TOvcLabel
          Left = 696
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatSvidLbl13: TOvcLabel
          Left = 744
          Top = 96
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower0: TOvcLabel
          Left = 120
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower1: TOvcLabel
          Left = 168
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower2: TOvcLabel
          Left = 216
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower3: TOvcLabel
          Left = 264
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower4: TOvcLabel
          Left = 312
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower5: TOvcLabel
          Left = 360
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower6: TOvcLabel
          Left = 408
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower7: TOvcLabel
          Left = 456
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower8: TOvcLabel
          Left = 504
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower9: TOvcLabel
          Left = 552
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower10: TOvcLabel
          Left = 600
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower11: TOvcLabel
          Left = 648
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower12: TOvcLabel
          Left = 696
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object ChanStatPower13: TOvcLabel
          Left = 744
          Top = 152
          Width = 41
          Height = 33
          Alignment = taCenter
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
      end
      object BitResultsSheet: TTabSheet
        Caption = 'BIT'
        ImageIndex = 2
        object OvcLabel9: TOvcLabel
          Left = 0
          Top = 0
          Width = 1244
          Height = 35
          Align = alTop
          Alignment = taCenter
          Caption = 'BIT Results'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = [fsUnderline]
          ParentFont = False
        end
        object OvcLabel10: TOvcLabel
          Left = 368
          Top = 48
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'x1:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel11: TOvcLabel
          Left = 368
          Top = 88
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'x2:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel12: TOvcLabel
          Left = 368
          Top = 136
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'x3:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object Bitx1Lbl: TOvcLabel
          Left = 464
          Top = 48
          Width = 89
          Height = 33
          Caption = 'Passed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object Bitx2Lbl: TOvcLabel
          Left = 464
          Top = 88
          Width = 89
          Height = 33
          Caption = 'Passed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object Bitx3Lbl: TOvcLabel
          Left = 464
          Top = 136
          Width = 89
          Height = 33
          Caption = 'Passed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel13: TOvcLabel
          Left = 688
          Top = 48
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Interrupt:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel14: TOvcLabel
          Left = 688
          Top = 88
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Ocxo:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel15: TOvcLabel
          Left = 688
          Top = 136
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'PLL:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object BitIntLbl: TOvcLabel
          Left = 784
          Top = 48
          Width = 89
          Height = 33
          Caption = 'Passed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object BitOcxoLbl: TOvcLabel
          Left = 784
          Top = 88
          Width = 89
          Height = 33
          Caption = 'Passed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object BitPllLbl: TOvcLabel
          Left = 784
          Top = 136
          Width = 89
          Height = 33
          Caption = 'Passed'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel22: TOvcLabel
          Left = 112
          Top = 88
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Time:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel20: TOvcLabel
          Left = 112
          Top = 48
          Width = 89
          Height = 35
          Alignment = taRightJustify
          Caption = 'Date:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object BitDateLbl: TOvcLabel
          Left = 208
          Top = 48
          Width = 137
          Height = 35
          Caption = '01/01/2001'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object BitTimeLbl: TOvcLabel
          Left = 208
          Top = 88
          Width = 137
          Height = 35
          Caption = '01/01/2001'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
      end
      object SysCfgSheet: TTabSheet
        Caption = 'System Config'
        ImageIndex = 3
        object OvcLabel16: TOvcLabel
          Left = 0
          Top = 0
          Width = 1244
          Height = 35
          Align = alTop
          Alignment = taCenter
          Caption = 'System Configuration'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = [fsUnderline]
          ParentFont = False
        end
        object OvcLabel17: TOvcLabel
          Left = 32
          Top = 48
          Width = 145
          Height = 35
          Alignment = taRightJustify
          Caption = 'Num Chans:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object SysCfgNumChansLbl: TOvcLabel
          Left = 184
          Top = 48
          Width = 81
          Height = 25
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel18: TOvcLabel
          Left = 32
          Top = 104
          Width = 145
          Height = 35
          Alignment = taRightJustify
          Caption = 'L2 Capable:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object SysCfgL2CapableLbl: TOvcLabel
          Left = 184
          Top = 104
          Width = 81
          Height = 25
          Appearance = apSunken
          Caption = 'False'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel19: TOvcLabel
          Left = 360
          Top = 56
          Width = 193
          Height = 35
          Alignment = taRightJustify
          Caption = 'Min Power (dBm):'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object SysCfgMinPowerLbl: TOvcLabel
          Left = 560
          Top = 56
          Width = 81
          Height = 25
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object SysCfgMaxPowerLbl: TOvcLabel
          Left = 560
          Top = 104
          Width = 81
          Height = 25
          Appearance = apSunken
          Caption = '0'
          ColorScheme = csCustom
          CustomSettings.HighlightDirection = sdDownRight
          CustomSettings.ShadowDirection = sdUpLeft
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel21: TOvcLabel
          Left = 360
          Top = 104
          Width = 193
          Height = 35
          Alignment = taRightJustify
          Caption = 'Max Power (dBm):'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -20
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
      end
    end
  end
  object MainPnl: TRzPanel
    Left = 0
    Top = 272
    Width = 1252
    Height = 677
    Align = alClient
    TabOrder = 1
    object LeftSizePnl: TRzSizePanel
      Left = 2
      Top = 2
      Width = 390
      Height = 673
      TabOrder = 0
      object LeftPnl: TRzPanel
        Left = 0
        Top = 0
        Width = 385
        Height = 673
        Align = alClient
        TabOrder = 0
        inline MsgListFrame: TMsgListFrame
          Left = 2
          Top = 2
          Width = 381
          Height = 669
          Align = alClient
          inherited MsgListPanel: TPanel
            Width = 381
            Height = 669
            inherited MsgListsb: TStatusBar
              Top = 650
              Width = 381
            end
            inherited MsgListTopPanel: TPanel
              Width = 381
            end
            inherited MsgListBox: TRzTabbedListBox
              Width = 381
              Height = 601
              TabStops.Min = -2147483647
              TabStops.Max = 2147483647
            end
          end
        end
      end
    end
    object RightClientPnl: TRzPanel
      Left = 392
      Top = 2
      Width = 858
      Height = 673
      Align = alClient
      BorderOuter = fsNone
      TabOrder = 1
      object RzPanel1: TRzPanel
        Left = 0
        Top = 0
        Width = 858
        Height = 103
        Align = alTop
        TabOrder = 0
        object IntLbl: TOvcLabel
          Left = 2
          Top = 2
          Width = 854
          Height = 35
          Align = alTop
          Alignment = taCenter
          Caption = 'Simulator Status'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -33
          Font.Name = 'Times New Roman'
          Font.Style = [fsUnderline]
          ParentFont = False
        end
        object SimModeLbl: TOvcLabel
          Left = 432
          Top = 48
          Width = 193
          Height = 35
          Caption = 'IDLE'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
        object OvcLabel1: TOvcLabel
          Left = 176
          Top = 48
          Width = 246
          Height = 35
          Alignment = taRightJustify
          Caption = 'Simulator Mode:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Times New Roman'
          Font.Style = []
          ParentFont = False
        end
      end
      object RzPanel2: TRzPanel
        Left = 0
        Top = 103
        Width = 858
        Height = 570
        Align = alClient
        TabOrder = 1
        object RzPanel3: TRzPanel
          Left = 2
          Top = 2
          Width = 185
          Height = 566
          Align = alLeft
          TabOrder = 0
          object OvcLabel2: TOvcLabel
            Left = 2
            Top = 2
            Width = 181
            Height = 35
            Align = alTop
            Alignment = taCenter
            Caption = 'Commands'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -23
            Font.Name = 'Times New Roman'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object StartScenBtn: TRzBitBtn
            Left = 40
            Top = 72
            Width = 105
            Caption = 'Start Scen'
            TabOrder = 0
            OnClick = StartScenBtnClick
          end
          object InitGeoBtn: TRzBitBtn
            Left = 40
            Top = 112
            Width = 105
            Caption = 'Init Geo'
            TabOrder = 1
            OnClick = InitGeoBtnClick
          end
          object StartLocalBtn: TRzBitBtn
            Left = 40
            Top = 152
            Width = 105
            Caption = 'Start Local'
            TabOrder = 2
            OnClick = StartLocalBtnClick
          end
          object SetSvidBtn: TRzBitBtn
            Left = 40
            Top = 192
            Width = 105
            Caption = 'Set Svid'
            TabOrder = 3
            OnClick = SetSvidBtnClick
          end
          object SetPowerBtn: TRzBitBtn
            Left = 40
            Top = 232
            Width = 105
            Caption = 'Set Power'
            TabOrder = 4
            OnClick = SetPowerBtnClick
          end
          object StopBtn: TRzBitBtn
            Left = 40
            Top = 272
            Width = 105
            Caption = 'Stop'
            TabOrder = 5
            OnClick = StopBtnClick
          end
          object ShutdownBtn: TRzBitBtn
            Left = 40
            Top = 312
            Width = 105
            Caption = 'Shutdown'
            TabOrder = 6
            OnClick = ShutdownBtnClick
          end
          object QueryBtn: TRzBitBtn
            Left = 40
            Top = 352
            Width = 105
            Caption = 'Query'
            TabOrder = 7
            OnClick = QueryBtnClick
          end
        end
        object MsgDataPnl: TRzPanel
          Left = 187
          Top = 2
          Width = 669
          Height = 566
          Align = alClient
          BorderOuter = fsNone
          TabOrder = 1
          object RzPanel5: TRzPanel
            Left = 0
            Top = 0
            Width = 669
            Height = 41
            Align = alTop
            TabOrder = 0
            object CommandDataLbl: TOvcLabel
              Left = 2
              Top = 2
              Width = 665
              Height = 35
              Align = alTop
              Alignment = taCenter
              Caption = 'Command Data'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -23
              Font.Name = 'Times New Roman'
              Font.Style = [fsUnderline]
              ParentFont = False
            end
          end
          object RzPanel6: TRzPanel
            Left = 0
            Top = 503
            Width = 669
            Height = 63
            Align = alBottom
            TabOrder = 1
            object SendBtn: TRzButton
              Left = 184
              Top = 24
              Caption = 'Send'
              TabOrder = 0
              OnClick = SendBtnClick
            end
            object CancelBtn: TRzButton
              Left = 296
              Top = 24
              Cancel = True
              Caption = 'Cancel'
              TabOrder = 1
            end
          end
        end
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 949
    Width = 1252
    Height = 19
    Panels = <
      item
        Width = 150
      end
      item
        Width = 150
      end
      item
        Width = 150
      end>
    SimplePanel = False
  end
  object Timer: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TimerTimer
    Left = 1208
    Top = 273
  end
  object StBrowser1: TStBrowser
    SpecialRootFolder = sfNone
    Left = 1024
    Top = 346
  end
  object MainMenu1: TMainMenu
    Left = 1200
    Top = 16
    object Help1: TMenuItem
      Caption = 'Help'
      object AboutMenu: TMenuItem
        Caption = 'About'
        OnClick = AboutMenuClick
      end
    end
  end
end

object RemoteMainForm: TRemoteMainForm
  Left = 398
  Top = 99
  Width = 1364
  Height = 1036
  ActiveControl = UpdateRateEdt
  Caption = 'Tapestry Closed Loop Control'
  Color = clBtnFace
  ParentFont = True
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
  OldCreateOrder = False
  Position = poDesktopCenter
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object SelInterfacesb: TStatusBar
    Left = 0
    Top = 935
    Width = 1356
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object BottomPnl: TRzPanel
    Left = 0
    Top = 954
    Width = 1356
    Height = 55
    Align = alBottom
    BorderOuter = fsFlat
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object CancelBtn: TRzButton
      Left = 793
      Top = 8
      Width = 61
      Height = 40
      Cancel = True
      Caption = 'Cancel'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TextStyle = tsRecessed
      OnClick = CancelBtnClick
    end
    object OKBtn: TRzButton
      Left = 715
      Top = 8
      Width = 61
      Height = 40
      Cancel = True
      Caption = 'OK'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TextStyle = tsRecessed
      OnClick = OKBtnClick
    end
  end
  object ClientPnl: TRzPanel
    Left = 0
    Top = 298
    Width = 1356
    Height = 637
    Align = alClient
    BorderOuter = fsGroove
    TabOrder = 2
    object SelScenTopPnl: TRzPanel
      Left = 2
      Top = 2
      Width = 1352
      Height = 116
      Align = alTop
      BorderOuter = fsGroove
      TabOrder = 0
      object SelTypeLbl: TOvcLabel
        Left = 228
        Top = 24
        Width = 310
        Height = 40
        Alignment = taRightJustify
        Caption = 'Selected Scenario:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -27
        Font.Name = 'Times New Roman'
        Font.Style = []
      end
      object SelLbl: TOvcLabel
        Left = 559
        Top = 24
        Width = 436
        Height = 40
        Appearance = apSunken
        Caption = '(none selected)'
        ColorScheme = csCustom
        CustomSettings.HighlightDirection = sdDownRight
        CustomSettings.ShadowDirection = sdUpLeft
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clActiveCaption
        Font.Height = -27
        Font.Name = 'Times New Roman'
        Font.Style = []
      end
      object BuiltDispLbl: TOvcLabel
        Left = 416
        Top = 70
        Width = 122
        Height = 28
        Alignment = taRightJustify
        Caption = 'Built: '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Times New Roman'
        Font.Style = []
      end
      object BuiltDateTimeLbl: TOvcLabel
        Left = 559
        Top = 70
        Width = 449
        Height = 28
        Appearance = apSunken
        Caption = '...'
        ColorScheme = csCustom
        CustomSettings.HighlightDirection = sdDownRight
        CustomSettings.ShadowDirection = sdUpLeft
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clActiveCaption
        Font.Height = -16
        Font.Name = 'Times New Roman'
        Font.Style = []
      end
      object SelTypeBtn: TO32FlexButton
        Left = 39
        Top = 26
        Width = 163
        Height = 40
        Caption = 'Scenario'
        TabOrder = 0
        OnClick = SelTypeBtnClick
        Glyph.Data = {
          66010000424D6601000000000000760000002800000014000000140000000100
          040000000000F000000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
          0008888800008800088888800000888800008000008888800000888800008000
          0088888800008888000088000088808888808888000088888088808888808888
          0000000000000000000000000000888880888088888088880000000000000000
          0000000000008888808880888880888800000000000000000000000000008888
          8088808888808888000000000000000000000000000088888088808888808888
          0000888880888088888088880000888888888000088888880000888888888000
          0088888800008888888880000088888800008888888888000888888800008888
          88888888888888880000}
        Layout = blGlyphRight
        ActiveItem = 0
        ItemCollection = <
          item
            About = 'v4.05'
            Caption = 'Scenario'
            BtnLayout = blGlyphRight
            Glyph.Data = {
              66010000424D6601000000000000760000002800000014000000140000000100
              040000000000F000000000000000000000001000000000000000000000000000
              8000008000000080800080000000800080008080000080808000C0C0C0000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
              0008888800008800088888800000888800008000008888800000888800008000
              0088888800008888000088000088808888808888000088888088808888808888
              0000000000000000000000000000888880888088888088880000000000000000
              0000000000008888808880888880888800000000000000000000000000008888
              8088808888808888000000000000000000000000000088888088808888808888
              0000888880888088888088880000888888888000088888880000888888888000
              0088888800008888888880000088888800008888888888000888888800008888
              88888888888888880000}
          end
          item
            About = 'v4.05'
            Caption = 'Vehicle Truth File'
            BtnLayout = blGlyphRight
            Glyph.Data = {
              66010000424D6601000000000000760000002800000014000000140000000100
              040000000000F000000000000000000000001000000000000000000000000000
              8000008000000080800080000000800080008080000080808000C0C0C0000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
              88888888000088888888CFFFC88888880000888888CCCCCCCC38888800008888
              CC3CCCCCCCA388880000888CCC3CCCCCCCAA3888000088CCCCA3CCCCCC3AA888
              000088CC33AA3CCCCCAAAA8800008CCCAAAAACCCCCAAAA8800008CCCAAAA3CCC
              CCAAAA8800008CCCAAA23CCCCCAAAAA800008CC33333CCCCAAAA3AA800008A33
              CCCACCCCAA3AAAA800008AAAAAACCCCCAA3AA3A800008AAAAA3ACCCCACCCCC88
              000088AAAA3ACCCCCCCACC880000888AAA3CCCCAAAAAA88800008888AAAC3CCA
              AAAA88880000888888AA3FFAAAA8888800008888888888888888888800008888
              88888888888888880000}
          end>
        PopRowCount = 2
        PopWidth = 200
        SmartPop = False
        OnMenuClick = SelTypeBtnMenuClick
        OnItemChange = SelTypeBtnItemChange
      end
    end
    object SelScenTreePnl: TRzSizePanel
      Left = 2
      Top = 118
      Width = 310
      Height = 517
      TabOrder = 1
      UseGradients = True
      object SelScenTreeView: TStShellTreeView
        Left = 0
        Top = 0
        Width = 305
        Height = 517
        CompressedColor = clBlue
        ExpandInterval = 2000
        Filtered = False
        ListView = SelScenListView
        Options = [toExpandTopNode, toShellMenu]
        SpecialRootFolder = sfDesktop
        SpecialStartInFolder = sfNone
        OnFolderSelected = SelScenTreeViewFolderSelected
        Align = alClient
        Color = clBtnFace
        Indent = 19
        ParentColor = False
        ShowRoot = False
        TabOrder = 0
        OnDblClick = SelScenTreeViewDblClick
      end
    end
    object SelScenListPnl: TRzPanel
      Left = 312
      Top = 118
      Width = 1042
      Height = 517
      Align = alClient
      TabOrder = 2
      object ListSizePnl: TRzSizePanel
        Left = 2
        Top = 2
        Width = 356
        Height = 513
        TabOrder = 0
        UseGradients = True
        object SelScenListView: TStShellListView
          Left = 0
          Top = 0
          Width = 351
          Height = 513
          CompressedColor = clBlue
          Filtered = False
          OpenDialogMode = False
          Optimization = otEnumerate
          Options = [loAllowRename, loAllowDrag, loAllowDrop, loShellMenu]
          SpecialRootFolder = sfNone
          TreeView = SelScenTreeView
          ViewStyle = vsList
          OnItemSelected = SelScenListViewItemSelected
          Align = alClient
          Color = clBtnFace
          MultiSelect = False
          ReadOnly = False
          TabOrder = 0
        end
      end
      object NavStatePnl: TRzSizePanel
        Left = 358
        Top = 2
        Width = 682
        Height = 513
        Align = alClient
        TabOrder = 1
        UseGradients = True
        object NavStatePageCtrl: TPageControl
          Left = 0
          Top = 0
          Width = 682
          Height = 513
          ActivePage = StartSheet
          Align = alClient
          MultiLine = True
          Style = tsButtons
          TabIndex = 0
          TabOrder = 0
          object StartSheet: TTabSheet
            Caption = 'Start'
            inline StartNavStateFrame: TNavStateFrame
              Left = 0
              Top = 0
              Width = 674
              Height = 482
              Align = alClient
              TabOrder = 0
              inherited NavPanel: TPanel
                Width = 674
                Height = 482
                inherited Label1: TLabel
                  Left = 26
                  Top = 59
                end
                inherited Label2: TLabel
                  Left = 26
                  Top = 85
                end
                inherited Label3: TLabel
                  Left = 198
                  Top = 59
                end
                inherited Label4: TLabel
                  Left = 181
                  Top = 85
                end
                inherited Label5: TLabel
                  Left = 59
                  Top = 117
                  Width = 83
                  Height = 13
                  Font.Height = -11
                end
                inherited Label6: TLabel
                  Left = 34
                  Top = 150
                end
                inherited LatLbl: TLabel
                  Left = 143
                  Top = 150
                end
                inherited Label7: TLabel
                  Left = 31
                  Top = 176
                end
                inherited LonLbl: TLabel
                  Left = 143
                  Top = 176
                end
                inherited Label11: TLabel
                  Left = 37
                  Top = 202
                end
                inherited AltLbl: TLabel
                  Left = 147
                  Top = 202
                end
                inherited Label8: TLabel
                  Left = 272
                  Top = 117
                  Width = 62
                  Height = 13
                  Font.Height = -11
                end
                inherited Label12: TLabel
                  Left = 18
                  Top = 228
                end
                inherited SpeedLbl: TLabel
                  Left = 147
                  Top = 228
                end
                inherited Label13: TLabel
                  Left = 232
                  Top = 150
                end
                inherited VelNorthLbl: TLabel
                  Left = 357
                  Top = 150
                end
                inherited Label15: TLabel
                  Left = 237
                  Top = 176
                end
                inherited VelEastLbl: TLabel
                  Left = 357
                  Top = 176
                end
                inherited Label17: TLabel
                  Left = 230
                  Top = 202
                end
                inherited VelDownLbl: TLabel
                  Left = 357
                  Top = 202
                end
                inherited Label19: TLabel
                  Left = 213
                  Top = 228
                end
                inherited HeadingLbl: TLabel
                  Left = 357
                  Top = 228
                end
                inherited Label14: TLabel
                  Left = 59
                  Top = 273
                  Width = 67
                  Height = 13
                  Font.Height = -11
                end
                inherited Label16: TLabel
                  Left = 273
                  Top = 273
                  Width = 67
                  Height = 13
                  Font.Height = -11
                end
                inherited Label18: TLabel
                  Left = 42
                  Top = 299
                end
                inherited PosEcefXLbl: TLabel
                  Left = 143
                  Top = 299
                end
                inherited Label21: TLabel
                  Left = 42
                  Top = 325
                end
                inherited PosEcefYLbl: TLabel
                  Left = 143
                  Top = 325
                end
                inherited Label23: TLabel
                  Left = 42
                  Top = 351
                end
                inherited PosEcefZLbl: TLabel
                  Left = 143
                  Top = 351
                end
                inherited Label25: TLabel
                  Left = 255
                  Top = 299
                end
                inherited VelEcefXLbl: TLabel
                  Left = 357
                  Top = 299
                end
                inherited Label27: TLabel
                  Left = 254
                  Top = 325
                end
                inherited VelEcefYLbl: TLabel
                  Left = 357
                  Top = 325
                end
                inherited Label29: TLabel
                  Left = 255
                  Top = 351
                end
                inherited VelEcefZLbl: TLabel
                  Left = 357
                  Top = 351
                end
                inherited Image1: TImage
                  Left = 20
                  Top = 117
                  Width = 16
                  Height = 16
                end
                inherited Image2: TImage
                  Left = 20
                  Top = 273
                  Width = 16
                  Height = 16
                end
                inherited DateTxt: TStaticText
                  Left = 59
                  Top = 59
                  Width = 81
                  Height = 16
                end
                inherited TimeTxt: TStaticText
                  Left = 59
                  Top = 85
                  Width = 81
                  Height = 16
                end
                inherited GpsWeekTxt: TStaticText
                  Left = 272
                  Top = 59
                  Width = 81
                  Height = 16
                end
                inherited GpsSecTxt: TStaticText
                  Left = 272
                  Top = 85
                  Width = 81
                  Height = 16
                end
                inherited LatTxt: TStaticText
                  Left = 59
                  Top = 150
                  Width = 81
                  Height = 16
                end
                inherited LonTxt: TStaticText
                  Left = 59
                  Top = 176
                  Width = 81
                  Height = 16
                end
                inherited AltTxt: TStaticText
                  Left = 59
                  Top = 202
                  Width = 81
                  Height = 16
                end
                inherited SpeedTxt: TStaticText
                  Left = 59
                  Top = 228
                  Width = 81
                  Height = 16
                end
                inherited VelNorthTxt: TStaticText
                  Left = 272
                  Top = 150
                  Width = 81
                  Height = 16
                end
                inherited VelEastTxt: TStaticText
                  Left = 272
                  Top = 176
                  Width = 81
                  Height = 16
                end
                inherited VelDownTxt: TStaticText
                  Left = 272
                  Top = 202
                  Width = 81
                  Height = 16
                end
                inherited HeadingTxt: TStaticText
                  Left = 272
                  Top = 228
                  Width = 81
                  Height = 16
                end
                inherited PosEcefXTxt: TStaticText
                  Left = 59
                  Top = 299
                  Width = 81
                  Height = 16
                end
                inherited PosEcefYTxt: TStaticText
                  Left = 59
                  Top = 325
                  Width = 81
                  Height = 16
                end
                inherited PosEcefZTxt: TStaticText
                  Left = 59
                  Top = 351
                  Width = 81
                  Height = 16
                end
                inherited VelEcefXTxt: TStaticText
                  Left = 272
                  Top = 299
                  Width = 81
                  Height = 16
                end
                inherited VelEcefYTxt: TStaticText
                  Left = 272
                  Top = 325
                  Width = 81
                  Height = 16
                end
                inherited VelEcefZTxt: TStaticText
                  Left = 272
                  Top = 351
                  Width = 81
                  Height = 16
                end
                inherited TopPnl: TRzPanel
                  Width = 674
                  inherited TopClientPnl: TRzPanel
                    Width = 618
                    inherited NavStateLbl: TOvcLabel
                      Width = 618
                      Font.Height = -25
                    end
                  end
                end
              end
            end
          end
          object EndSheet: TTabSheet
            Caption = 'End'
            ImageIndex = 1
            inline EndNavStateFrame: TNavStateFrame
              Left = 0
              Top = 0
              Width = 674
              Height = 596
              Align = alClient
              TabOrder = 0
              inherited NavPanel: TPanel
                Width = 674
                Height = 596
                inherited Label1: TLabel
                  Left = 26
                  Top = 59
                end
                inherited Label2: TLabel
                  Left = 26
                  Top = 85
                end
                inherited Label3: TLabel
                  Left = 182
                  Top = 59
                end
                inherited Label4: TLabel
                  Left = 165
                  Top = 85
                end
                inherited Label5: TLabel
                  Left = 59
                  Top = 117
                  Width = 83
                  Height = 13
                  Font.Height = -11
                end
                inherited Label6: TLabel
                  Left = 34
                  Top = 150
                end
                inherited LatLbl: TLabel
                  Left = 143
                  Top = 150
                end
                inherited Label7: TLabel
                  Left = 31
                  Top = 176
                end
                inherited LonLbl: TLabel
                  Left = 143
                  Top = 176
                end
                inherited Label11: TLabel
                  Left = 37
                  Top = 202
                end
                inherited AltLbl: TLabel
                  Left = 147
                  Top = 202
                end
                inherited Label8: TLabel
                  Left = 256
                  Top = 117
                  Width = 62
                  Height = 13
                  Font.Height = -11
                end
                inherited Label12: TLabel
                  Left = 18
                  Top = 228
                end
                inherited SpeedLbl: TLabel
                  Left = 147
                  Top = 228
                end
                inherited Label13: TLabel
                  Left = 216
                  Top = 150
                end
                inherited VelNorthLbl: TLabel
                  Left = 340
                  Top = 150
                end
                inherited Label15: TLabel
                  Left = 221
                  Top = 176
                end
                inherited VelEastLbl: TLabel
                  Left = 340
                  Top = 176
                end
                inherited Label17: TLabel
                  Left = 214
                  Top = 202
                end
                inherited VelDownLbl: TLabel
                  Left = 340
                  Top = 202
                end
                inherited Label19: TLabel
                  Left = 197
                  Top = 228
                end
                inherited HeadingLbl: TLabel
                  Left = 340
                  Top = 228
                end
                inherited Label14: TLabel
                  Left = 59
                  Top = 273
                  Width = 67
                  Height = 13
                  Font.Height = -11
                end
                inherited Label16: TLabel
                  Left = 257
                  Top = 273
                  Width = 67
                  Height = 13
                  Font.Height = -11
                end
                inherited Label18: TLabel
                  Left = 42
                  Top = 299
                end
                inherited PosEcefXLbl: TLabel
                  Left = 143
                  Top = 299
                end
                inherited Label21: TLabel
                  Left = 42
                  Top = 325
                end
                inherited PosEcefYLbl: TLabel
                  Left = 143
                  Top = 325
                end
                inherited Label23: TLabel
                  Left = 42
                  Top = 351
                end
                inherited PosEcefZLbl: TLabel
                  Left = 143
                  Top = 351
                end
                inherited Label25: TLabel
                  Left = 239
                  Top = 299
                end
                inherited VelEcefXLbl: TLabel
                  Left = 340
                  Top = 299
                end
                inherited Label27: TLabel
                  Left = 238
                  Top = 325
                end
                inherited VelEcefYLbl: TLabel
                  Left = 340
                  Top = 325
                end
                inherited Label29: TLabel
                  Left = 239
                  Top = 351
                end
                inherited VelEcefZLbl: TLabel
                  Left = 340
                  Top = 351
                end
                inherited Image1: TImage
                  Left = 20
                  Top = 117
                  Width = 16
                  Height = 16
                end
                inherited Image2: TImage
                  Left = 20
                  Top = 273
                  Width = 16
                  Height = 16
                end
                inherited DateTxt: TStaticText
                  Left = 59
                  Top = 59
                  Width = 81
                  Height = 16
                end
                inherited TimeTxt: TStaticText
                  Left = 59
                  Top = 85
                  Width = 81
                  Height = 16
                end
                inherited GpsWeekTxt: TStaticText
                  Left = 256
                  Top = 59
                  Width = 81
                  Height = 16
                end
                inherited GpsSecTxt: TStaticText
                  Left = 256
                  Top = 85
                  Width = 81
                  Height = 16
                end
                inherited LatTxt: TStaticText
                  Left = 59
                  Top = 150
                  Width = 81
                  Height = 16
                end
                inherited LonTxt: TStaticText
                  Left = 59
                  Top = 176
                  Width = 81
                  Height = 16
                end
                inherited AltTxt: TStaticText
                  Left = 59
                  Top = 202
                  Width = 81
                  Height = 16
                end
                inherited SpeedTxt: TStaticText
                  Left = 59
                  Top = 228
                  Width = 81
                  Height = 16
                end
                inherited VelNorthTxt: TStaticText
                  Left = 256
                  Top = 150
                  Width = 81
                  Height = 16
                end
                inherited VelEastTxt: TStaticText
                  Left = 256
                  Top = 176
                  Width = 81
                  Height = 16
                end
                inherited VelDownTxt: TStaticText
                  Left = 256
                  Top = 202
                  Width = 81
                  Height = 16
                end
                inherited HeadingTxt: TStaticText
                  Left = 256
                  Top = 228
                  Width = 81
                  Height = 16
                end
                inherited PosEcefXTxt: TStaticText
                  Left = 59
                  Top = 299
                  Width = 81
                  Height = 16
                end
                inherited PosEcefYTxt: TStaticText
                  Left = 59
                  Top = 325
                  Width = 81
                  Height = 16
                end
                inherited PosEcefZTxt: TStaticText
                  Left = 59
                  Top = 351
                  Width = 81
                  Height = 16
                end
                inherited VelEcefXTxt: TStaticText
                  Left = 256
                  Top = 299
                  Width = 81
                  Height = 16
                end
                inherited VelEcefYTxt: TStaticText
                  Left = 256
                  Top = 325
                  Width = 81
                  Height = 16
                end
                inherited VelEcefZTxt: TStaticText
                  Left = 256
                  Top = 351
                  Width = 81
                  Height = 16
                end
              end
            end
          end
        end
      end
    end
  end
  object InterfaceSizePnl: TRzSizePanel
    Left = 0
    Top = 0
    Width = 1356
    Height = 298
    Align = alTop
    TabOrder = 3
    UseGradients = True
    object LeftInterfacePnl: TRzPanel
      Left = 0
      Top = 0
      Width = 545
      Height = 293
      Align = alLeft
      BorderOuter = fsFlat
      TabOrder = 0
      object BottomIntPnl: TRzPanel
        Left = 1
        Top = 224
        Width = 543
        Height = 68
        Align = alBottom
        BorderOuter = fsFlat
        TabOrder = 0
        object UpdateMsgTypeLbl: TOvcLabel
          Left = 39
          Top = 14
          Width = 183
          Height = 22
          Alignment = taRightJustify
          Appearance = apNone
          Caption = 'Trajectory Msg Rate (Hz):'
          ColorScheme = csCustom
          CustomSettings.HighlightDepth = 0
          CustomSettings.HighlightDirection = sdNone
          CustomSettings.ShadowDepth = 0
          CustomSettings.ShadowDirection = sdNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
        end
        object OvcLabel2: TOvcLabel
          Left = 39
          Top = 40
          Width = 183
          Height = 22
          Alignment = taRightJustify
          Appearance = apNone
          Caption = 'Preload Time (s):'
          ColorScheme = csCustom
          CustomSettings.HighlightDepth = 0
          CustomSettings.HighlightDirection = sdNone
          CustomSettings.ShadowDepth = 0
          CustomSettings.ShadowDirection = sdNone
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
        end
        object UpdateRateEdt: TRzSpinEdit
          Left = 234
          Top = 16
          Width = 53
          Height = 21
          Max = 20
          Min = 1
          Value = 10
          Color = clBtnFace
          FlatButtons = True
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Verdana'
          Font.Style = []
          FrameHotTrack = True
          FrameVisible = True
          ParentFont = False
          TabOrder = 0
        end
        object PreloadEdt: TRzSpinEdit
          Left = 234
          Top = 42
          Width = 53
          Height = 21
          Increment = 0.05
          IntegersOnly = False
          Max = 20
          Value = 1
          Color = clBtnFace
          FlatButtons = True
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Verdana'
          Font.Style = []
          FrameHotTrack = True
          FrameVisible = True
          ParentFont = False
          TabOrder = 1
        end
      end
      object IntTopPnl: TRzPanel
        Left = 1
        Top = 1
        Width = 543
        Height = 156
        Align = alClient
        BorderOuter = fsFlat
        TabOrder = 1
        object OvcLabel1: TOvcLabel
          Left = 26
          Top = 13
          Width = 196
          Height = 40
          Alignment = taRightJustify
          Caption = 'Select Interface:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -27
          Font.Name = 'Times New Roman'
          Font.Style = []
        end
        object SimModeLbl: TOvcLabel
          Left = 39
          Top = 81
          Width = 183
          Height = 22
          Alignment = taRightJustify
          Caption = 'Simulation Mode:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Times New Roman'
          Font.Style = []
        end
        object IntProtocolLbl: TOvcLabel
          Left = 39
          Top = 115
          Width = 183
          Height = 22
          Alignment = taRightJustify
          Caption = 'Interface Protocol:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Times New Roman'
          Font.Style = []
        end
        object InterfaceFlexBtn: TO32FlexButton
          Left = 234
          Top = 13
          Width = 111
          Height = 41
          Hint = 'Select the type of interface'
          Caption = 'GPIB'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Glyph.Data = {
            42010000424D4201000000000000760000002800000011000000110000000100
            040000000000CC00000000000000000000001000000010000000000000000000
            BF0000BF000000BFBF00BF000000BF00BF00BFBF0000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
            7777700000007777777777777777700000007777777777777777700000007777
            7777777777777000000077777777000000007000000077777777777777777000
            0000777777777770000070000000777747777777777770000000777744777770
            0000700000007744444777777777700000007477447777700000700000007477
            4777777777777000000074777777000000007000000074777777777777777000
            0000774444444777777770000000777777777777777770000000777777777777
            777770000000}
          Style = bsNew
          ActiveItem = 0
          ItemCollection = <
            item
              About = 'v4.05'
              Caption = 'GPIB'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                42010000424D4201000000000000760000002800000011000000110000000100
                040000000000CC00000000000000000000001000000010000000000000000000
                BF0000BF000000BFBF00BF000000BF00BF00BFBF0000C0C0C000808080000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
                7777700000007777777777777777700000007777777777777777700000007777
                7777777777777000000077777777000000007000000077777777777777777000
                0000777777777770000070000000777747777777777770000000777744777770
                0000700000007744444777777777700000007477447777700000700000007477
                4777777777777000000074777777000000007000000074777777777777777000
                0000774444444777777770000000777777777777777770000000777777777777
                777770000000}
            end
            item
              About = 'v4.05'
              Caption = 'Serial Port'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                36030000424D3603000000000000360000002800000010000000100000000100
                1800000000000003000000000000000000000000000000000000FFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFBFBFBF7F7F7F7F7F7F7F7F7FFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFF
                FFFFBFBFBF7F7F7FBFBFBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F7F7FFFFFFFFFFFFFBFBFBFBFBFBFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F
                7F7FFFFFFF7F7F7FFFFFFF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F7F7FFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFF00
                0000FFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFFFFFFFFFFFF000000FFFFFF7F7F7FFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F
                7F7FFFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F7F7FFFFFFF7F7F7FFFFFFF7F7F7FFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFF
                FFFFFFFFFF7F7F7FFFFFFF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFF000000FFFFFFFFFFFFFFFFFF7F7F7FFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFF
                FFFFFFFFFF000000FFFFFF7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F7F7FFFFFFFFFFFFFFFFFFF7F7F7FFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7FFFFFFF7F
                7F7FFFFFFFFFFFFF3F3F3FBFBFBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFF7F7F7FFFFFFFFFFFFFBFBFBF3F3F3FBFBFBFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFBFBF7F7F7F7F
                7F7F7F7F7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
            end
            item
              About = 'v4.05'
              Caption = 'Ethernet'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                36030000424D3603000000000000360000002800000010000000100000000100
                1800000000000003000000000000000000000000000000000000FFFFFFFFFFFF
                202020FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FF202020FFFFFFFFFFFFFFFFFF000000404040FFFFFFFFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000606060FFFFFFFFFFFFFFFFFF000000
                404040FFFFFFFFFFFF404040404040202020FFFFFFFFFFFFFFFFFF4040402020
                20404040404040202020FFFFFF000000404040FFFFFF00000000000000000020
                2020202020FFFFFF3030307F7F7F7F7F7F7F7F7F7F7F7F606060FFFFFF000000
                404040000000404040FFFFFFFFFFFF000000404040FFFFFF606060C0C0C0C0C0
                C0C0C0C0DFDFDF404040FFFFFF000000404040000000404040FFFFFFFFFFFF00
                0000606060202020606060C0C0C0C0C0C0C0C0C0DFDFDF404040FFFFFF000000
                404040000000404040FFFFFF000000DFDFDF6F6F6F404040606060C0C0C0C0C0
                C0C0C0C0DFDFDF404040FFFFFF000000606060000000606060FFFFFF000000DF
                DFDF6F6F6F404040606060C0C0C0C0C0C0C0C0C0CFCFCF202020000000202020
                202020202020202020606060000000DFDFDF6F6F6F4040400000002020202020
                20202020202020FFFFFF606060DFDFDFDFDFDFDFDFDFEFEFEF404040000000DF
                DFDF6F6F6F404040FFFFFF000000202020000000202020FFFFFF606060C0C0C0
                C0C0C0C0C0C0DFDFDF404040000000DFDFDF6F6F6F202020FFFFFF0000004040
                40000000404040FFFFFF606060C0C0C0C0C0C0C0C0C0DFDFDF404040FFFFFF00
                0000202020FFFFFFFFFFFF000000404040000000404040FFFFFF606060C0C0C0
                C0C0C0C0C0C0DFDFDF404040FFFFFF000000404040FFFFFFFFFFFF0000002020
                20000000404040FFFFFF303030606060606060606060606060000000FFFFFFFF
                FFFF000000404040404040000000FFFFFF000000404040FFFFFFFFFFFFFFFFFF
                202020202020FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
                FF000000404040FFFFFFFFFFFFFFFFFF000000202020FFFFFFFFFFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000202020FFFFFF}
            end>
          PopRowCount = 3
          PopWidth = 100
          SmartPop = False
          OnItemChange = InterfaceFlexBtnItemChange
        end
        object SimModeBtn: TO32FlexButton
          Left = 234
          Top = 83
          Width = 111
          Height = 24
          Caption = 'Trajectory'
          TabOrder = 1
          Glyph.Data = {
            66010000424D6601000000000000760000002800000014000000140000000100
            040000000000F000000000000000000000001000000000000000000000000000
            8000008000000080800080000000800080008080000080808000C0C0C0000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
            88888888000088888888CFFFC88888880000888888CCCCCCCC38888800008888
            CC3CCCCCCCA388880000888CCC3CCCCCCCAA3888000088CCCCA3CCCCCC3AA888
            000088CC33AA3CCCCCAAAA8800008CCCAAAAACCCCCAAAA8800008CCCAAAA3CCC
            CCAAAA8800008CCCAAA23CCCCCAAAAA800008CC33333CCCCAAAA3AA800008A33
            CCCACCCCAA3AAAA800008AAAAAACCCCCAA3AA3A800008AAAAA3ACCCCACCCCC88
            000088AAAA3ACCCCCCCACC880000888AAA3CCCCAAAAAA88800008888AAAC3CCA
            AAAA88880000888888AA3FFAAAA8888800008888888888888888888800008888
            88888888888888880000}
          ActiveItem = 0
          ItemCollection = <
            item
              About = 'v4.05'
              Caption = 'Trajectory'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                66010000424D6601000000000000760000002800000014000000140000000100
                040000000000F000000000000000000000001000000000000000000000000000
                8000008000000080800080000000800080008080000080808000C0C0C0000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
                88888888000088888888CFFFC88888880000888888CCCCCCCC38888800008888
                CC3CCCCCCCA388880000888CCC3CCCCCCCAA3888000088CCCCA3CCCCCC3AA888
                000088CC33AA3CCCCCAAAA8800008CCCAAAAACCCCCAAAA8800008CCCAAAA3CCC
                CCAAAA8800008CCCAAA23CCCCCAAAAA800008CC33333CCCCAAAA3AA800008A33
                CCCACCCCAA3AAAA800008AAAAAACCCCCAA3AA3A800008AAAAA3ACCCCACCCCC88
                000088AAAA3ACCCCCCCACC880000888AAA3CCCCAAAAAA88800008888AAAC3CCA
                AAAA88880000888888AA3FFAAAA8888800008888888888888888888800008888
                88888888888888880000}
            end
            item
              About = 'v4.05'
              Caption = 'Range'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                66010000424D6601000000000000760000002800000014000000140000000100
                040000000000F000000000000000000000001000000000000000000000000000
                8000008000000080800080000000800080008080000080808000C0C0C0000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0FFFFF
                FFFFFFFF0000FFFFF030FFFF0000FFFF0000FFFF03B30FF0FFFF0FFF0000FFF0
                3B3B30FFF000F0FF0000FF03B3B3B30FFFFF0F0F0000F03B3B3B30F00F00F0F0
                000003B3B3B30F0770F0F0F00000F03B3B300073370FF0F00000FF03B3000773
                370FFFF00000FFF030F0733770F0FF0F0000FFFF0F0773370F030FFF0000FFFF
                F0733770003B30FF0000FFFFF073370003B3B30F0000FFFFFF0770F03B3B3B30
                0000FFFFFFF00F03B3B3B30F0000FFFFFFFFF03B3B3B30FF0000FFFFFFFFFF03
                B3B30FFF0000FFFFFFFFFFF03B30FFFF0000FFFFFFFFFFFF030FFFFF0000FFFF
                FFFFFFFFF0FFFFFF0000}
            end>
        end
        object IntProtocolBtn: TO32FlexButton
          Left = 234
          Top = 117
          Width = 111
          Height = 24
          Caption = 'STel 7224'
          TabOrder = 2
          Glyph.Data = {
            66010000424D6601000000000000760000002800000014000000140000000100
            040000000000F000000000000000000000001000000000000000000000000000
            8000008000000080800080000000800080008080000080808000C0C0C0000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0FFFFF
            FFFFFFFF0000FFFFF030FFFF0000FFFF0000FFFF03B30FF0FFFF0FFF0000FFF0
            3B3B30FFF000F0FF0000FF03B3B3B30FFFFF0F0F0000F03B3B3B30F00F00F0F0
            000003B3B3B30F0770F0F0F00000F03B3B300073370FF0F00000FF03B3000773
            370FFFF00000FFF030F0733770F0FF0F0000FFFF0F0773370F030FFF0000FFFF
            F0733770003B30FF0000FFFFF073370003B3B30F0000FFFFFF0770F03B3B3B30
            0000FFFFFFF00F03B3B3B30F0000FFFFFFFFF03B3B3B30FF0000FFFFFFFFFF03
            B3B30FFF0000FFFFFFFFFFF03B30FFFF0000FFFFFFFFFFFF030FFFFF0000FFFF
            FFFFFFFFF0FFFFFF0000}
          ActiveItem = 0
          ItemCollection = <
            item
              About = 'v4.05'
              Caption = 'STel 7224'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                66010000424D6601000000000000760000002800000014000000140000000100
                040000000000F000000000000000000000001000000000000000000000000000
                8000008000000080800080000000800080008080000080808000C0C0C0000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0FFFFF
                FFFFFFFF0000FFFFF030FFFF0000FFFF0000FFFF03B30FF0FFFF0FFF0000FFF0
                3B3B30FFF000F0FF0000FF03B3B3B30FFFFF0F0F0000F03B3B3B30F00F00F0F0
                000003B3B3B30F0770F0F0F00000F03B3B300073370FF0F00000FF03B3000773
                370FFFF00000FFF030F0733770F0FF0F0000FFFF0F0773370F030FFF0000FFFF
                F0733770003B30FF0000FFFFF073370003B3B30F0000FFFFFF0770F03B3B3B30
                0000FFFFFFF00F03B3B3B30F0000FFFFFFFFF03B3B3B30FF0000FFFFFFFFFF03
                B3B30FFF0000FFFFFFFFFFF03B30FFFF0000FFFFFFFFFFFF030FFFFF0000FFFF
                FFFFFFFFF0FFFFFF0000}
            end
            item
              About = 'v4.05'
              Caption = 'STel 7200'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                66010000424D6601000000000000760000002800000014000000140000000100
                040000000000F000000000000000000000001000000000000000000000000000
                8000008000000080800080000000800080008080000080808000C0C0C0000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF0FFFFF
                FFFFFFFF0000FFFFF030FFFF0000FFFF0000FFFF03B30FF0FFFF0FFF0000FFF0
                3B3B30FFF000F0FF0000FF03B3B3B30FFFFF0F0F0000F03B3B3B30F00F00F0F0
                000003B3B3B30F0770F0F0F00000F03B3B300073370FF0F00000FF03B3000773
                370FFFF00000FFF030F0733770F0FF0F0000FFFF0F0773370F030FFF0000FFFF
                F0733770003B30FF0000FFFFF073370003B3B30F0000FFFFFF0770F03B3B3B30
                0000FFFFFFF00F03B3B3B30F0000FFFFFFFFF03B3B3B30FF0000FFFFFFFFFF03
                B3B30FFF0000FFFFFFFFFFF03B30FFFF0000FFFFFFFFFFFF030FFFFF0000FFFF
                FFFFFFFFF0FFFFFF0000}
            end
            item
              About = 'v4.05'
              Caption = 'NavLabs'
              BtnLayout = blGlyphLeft
              Glyph.Data = {
                76020000424D7602000000000000760000002800000020000000200000000100
                0400000000000002000000000000000000001000000000000000000000000000
                8000008000000080800080000000800080008080000080808000C0C0C0000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
                FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF8888FFFFFFFF
                FFFFFFFFFFFF888888FF887777888FFFFFFFFFFF888777887757FFFF88877778
                FFFFF8877788FFFFFFF8888888FFF887778877788FFFFFFFFFFFFFFFF88888FF
                875778FFFFFFFFFFFFFFFFFFFFFFFF877778777FFFFFFFFFFFFFFFFFFFFFFF88
                7778F87577557788FFFFFFFFFFFF8788FF8774887778888777FFFFFFFFF8878F
                778F8878F8778FFF877FFFFFFF787878FF74444778F8778FFF77FFFFF77878FF
                F54444444888F877FF888FF87777FFFF7444444445FF78F778F88787778FFFF8
                44444444448FF87F8787F8557FFFFFF844444444447FFFF88F74877478FFFFF8
                44444444447FFFFF8774F74F877FFFF844444444447FFFFFF84784878F778FFF
                44444444448FFFFFF57888FF87F8778F8444444447FFFFFF74FF8FFFFF88F877
                884444447FFFFFF748FFFFFFFFFF78F877777778FFFFFF748FFFFFFFFFFFF878
                F87778FFFFFFF778FFFF8FFFFFFFFFF878F877788FF8778FFFFF88FFFFFFFFFF
                F878FF8777577FFFFFFFF7FFFFFFFFFFFFFF8788777777888888F778FFFFFFFF
                FFF88777778F88887777FF877778888777788F78788888FFFFFFFFFFF8887788
                FFFF8778FFFFF8888888FFFFFFFFFFFFFF8787FFFFFFFFFFFFFFFFFFFFFFFFFF
                87778FFFFFFFFFFFFFFFFFFFFFFFF877778FFFFFFFFFFFFFFFFF}
            end>
        end
      end
      inline InterfaceAccept: TInterfaceAcceptFrame
        Left = 1
        Top = 157
        Width = 543
        Height = 67
        Align = alBottom
        TabOrder = 2
        inherited InterfaceAcceptPnl: TRzPanel
          Width = 543
          BorderOuter = fsFlat
          inherited AcceptLbl: TOvcLabel
            Appearance = apNone
            ColorScheme = csCustom
            CustomSettings.HighlightDepth = 0
            CustomSettings.HighlightDirection = sdNone
            CustomSettings.ShadowDepth = 0
            CustomSettings.ShadowDirection = sdNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clGray
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
          end
          inherited AcceptInterfaceBtn: TRzBitBtn
            HotTrack = True
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              0400000000000001000000000000000000001000000000000000000000000000
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
          end
          inherited CancelInterfaceBtn: TRzBitBtn
            HotTrack = True
          end
        end
      end
    end
    object RightInterfacePnl: TRzPanel
      Left = 545
      Top = 0
      Width = 811
      Height = 293
      Align = alClient
      BorderOuter = fsFlat
      TabOrder = 1
    end
  end
  object CSGlobalObject1: TCSGlobalObject
    DestinationDetails = 'Viewer'
    Category = 'RemoteDriver'
    HexNumPrefix = '$'
    QuoteChar = #39
    Left = 506
    Top = 13
  end
end

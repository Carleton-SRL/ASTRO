object MsgListFrame: TMsgListFrame
  Left = 0
  Top = 0
  Width = 512
  Height = 357
  TabOrder = 0
  object TopPnl: TRzPanel
    Left = 0
    Top = 0
    Width = 512
    Height = 41
    Align = alTop
    BorderOuter = fsGroove
    TabOrder = 0
    object RzLabel2: TRzLabel
      Left = 8
      Top = 7
      Width = 49
      Height = 26
      Caption = 'Time into Simulation'
      WordWrap = True
      FrameSides = []
    end
    object RzLabel3: TRzLabel
      Left = 64
      Top = 20
      Width = 35
      Height = 13
      Caption = 'Source'
      FrameSides = []
    end
    object RzLabel1: TRzLabel
      Left = 120
      Top = 20
      Width = 25
      Height = 13
      Caption = 'Type'
      FrameSides = []
    end
  end
  object MsgListBox: TRzTabbedListBox
    Left = 0
    Top = 41
    Width = 512
    Height = 297
    TabStops.Min = -2147483647
    TabStops.Max = 2147483647
    TabStops.Integers = (
      10
      20
      31)
    Align = alClient
    Color = clBtnFace
    ItemHeight = 13
    Items.Strings = (
      
        '1000.00'#9'SIM'#9'Traj'#9'T=1001.15 P=34.0000 -118.0000 0.0 V=10.00 1.00 ' +
        '0.0')
    TabOrder = 1
  end
  object MsgListsb: TStatusBar
    Left = 0
    Top = 338
    Width = 512
    Height = 19
    Panels = <
      item
        Width = 200
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
end

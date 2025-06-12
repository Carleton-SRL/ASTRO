object MsgListFrame: TMsgListFrame
  Left = 0
  Top = 0
  Width = 505
  Height = 337
  TabOrder = 0
  object MsgListPanel: TPanel
    Left = 0
    Top = 0
    Width = 505
    Height = 337
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object MsgListsb: TStatusBar
      Left = 0
      Top = 318
      Width = 505
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
    object MsgListTopPanel: TPanel
      Left = 0
      Top = 0
      Width = 505
      Height = 49
      Align = alTop
      TabOrder = 1
      object RzLabel2: TRzLabel
        Left = 8
        Top = 8
        Width = 62
        Height = 32
        Caption = 'Time into Simulation'
        WordWrap = True
        FrameSides = []
      end
      object RzLabel3: TRzLabel
        Left = 80
        Top = 16
        Width = 43
        Height = 16
        Caption = 'Source'
        FrameSides = []
      end
      object RzLabel1: TRzLabel
        Left = 160
        Top = 16
        Width = 32
        Height = 16
        Caption = 'Type'
        FrameSides = []
      end
    end
    object MsgListBox: TRzTabbedListBox
      Left = 0
      Top = 49
      Width = 505
      Height = 269
      TabStops.Min = -2147483647
      TabStops.Max = 2147483647
      TabStops.Integers = (
        10
        20
        31)
      Align = alClient
      Color = clBtnFace
      ItemHeight = 16
      Items.Strings = (
        
          '1000.00'#9'SIM'#9'Traj'#9'T=1001.15 P=34.0000 -118.0000 0.0 V=10.00 1.00 ' +
          '0.0')
      TabOrder = 2
    end
  end
end

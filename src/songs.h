#ifndef SONGS_H
#define SONGS_H

#include <string>
#include <eadk.h>
#include <eadkpp.h>
#include <eadkpp_extended.h>
#include "palette.h"

namespace platform {
namespace songs {
    
class Song {
    const char* name;
    int length = 0;
    int speed = 1;
    int start = 0;
    std::vector<Button*> notes = {};

    public:
        Song() {
            this->name = "NONE";
            this->length = 0;
            this->speed = 1;
            this->notes = {};
        }

        Song(const char* name, int start, int length, int speed, std::vector<Button*> notes) {
            this->name = name;
            this->length = length;
            this->speed = speed;
            this->notes = notes;
            this->start = start;
        }

        int getStart() {
            return this->start;
        }

        const char* getName() {
            return this->name;
        }

        int getLength() {
            return this->length;
        }

        int getSpeed() {
            return this->speed;
        }

        std::vector<Button*> getNotes() {
            return this->notes;
        }
};

class SongManager {
    private:
        Song songs[3] = {
            Song("HIGH HOPES", 10000, 178990, 5, {new Button(10880,1),new Button(11210,1),new Button(11360,1),new Button(11570,1),new Button(11870,1),new Button(12220,1),new Button(12540,1),new Button(12690,1),new Button(12910,1),new Button(13230,1),new Button(13570,1),new Button(13920,1),new Button(14080,1),new Button(14310,1),new Button(14630,1),new Button(14930,1),new Button(15260,1),new Button(15430,1),new Button(15630,1),new Button(15800,1),new Button(15960,2),new Button(16280,3),new Button(16660,2),new Button(16990,3),new Button(17340,2),new Button(17530,3),new Button(17720,2),new Button(17870,3),new Button(18380,2),new Button(18570,3),new Button(18740,3),new Button(18900,2),new Button(19070,2),new Button(19380,3),new Button(19530,3),new Button(19730,2),new Button(19900,2),new Button(20070,3),new Button(20220,3),new Button(20390,4),new Button(20610,3),new Button(21030,4),new Button(21220,3),new Button(21420,4),new Button(21600,3),new Button(21740,2),new Button(22100,4),new Button(22320,2),new Button(22520,4),new Button(22660,1),new Button(22870,3),new Button(23020,1),new Button(23160,2),new Button(23750,3),new Button(23980,2),new Button(24150,2),new Button(24480,3),new Button(24800,4),new Button(25120,3),new Button(25280,3),new Button(25510,4),new Button(25820,3),new Button(26170,4),new Button(26330,4),new Button(26510,4),new Button(26590,3),new Button(26800,2),new Button(27150,3),new Button(27510,3),new Button(27830,3),new Button(28190,4),new Button(28350,4),new Button(28550,3),new Button(28680,2),new Button(29210,3),new Button(29370,3),new Button(29550,4),new Button(29780,2),new Button(30000,3),new Button(30230,3),new Button(30410,3),new Button(30550,2),new Button(30750,4),new Button(30960,1),new Button(31170,2),new Button(31350,3),new Button(31950,4),new Button(32170,4),new Button(32350,4),new Button(32660,4),new Button(33030,4),new Button(33360,4),new Button(33670,4),new Button(33840,4),new Button(34020,4),new Button(34190,4),new Button(34680,4),new Button(34840,4),new Button(35010,4),new Button(35340,3),new Button(35690,4),new Button(36050,3),new Button(36260,4),new Button(36420,4),new Button(36670,3),new Button(37010,4),new Button(37340,3),new Button(37530,2),new Button(37710,2),new Button(37740,3),new Button(38050,3),new Button(38420,2),new Button(38810,3),new Button(39130,2),new Button(39470,3),new Button(39790,2),new Button(40140,3),new Button(40470,2),new Button(40830,3),new Button(41170,2),new Button(41500,3),new Button(41840,2),new Button(42160,3),new Button(42520,2),new Button(42830,3),new Button(43170,2),new Button(43510,1),new Button(43770,2),new Button(44190,3),new Button(44530,4),new Button(44870,3),new Button(45180,2),new Button(45520,1),new Button(45920,2),new Button(46250,3),new Button(46570,4),new Button(46900,3),new Button(47270,2),new Button(47590,1),new Button(47930,2),new Button(48230,3),new Button(48600,4),new Button(48970,3),new Button(49300,2),new Button(49600,3),new Button(49990,2),new Button(50340,3),new Button(50700,2),new Button(51010,3),new Button(51350,2),new Button(51700,3),new Button(52030,2),new Button(52330,3),new Button(52700,2),new Button(53060,3),new Button(53400,2),new Button(53740,3),new Button(54080,2),new Button(54450,3),new Button(54780,2),new Button(55130,3),new Button(55580,2),new Button(55830,3),new Button(56100,2),new Button(56450,3),new Button(56820,2),new Button(57090,3),new Button(57310,2),new Button(57640,3),new Button(58040,2),new Button(58350,3),new Button(58730,2),new Button(59030,3),new Button(59360,1),new Button(59700,2),new Button(60030,3),new Button(60410,4),new Button(60730,3),new Button(61080,2),new Button(61420,1),new Button(61760,2),new Button(62080,3),new Button(62420,4),new Button(62740,3),new Button(63100,2),new Button(63440,1),new Button(63760,2),new Button(64110,3),new Button(64440,4),new Button(64780,3),new Button(65100,2),new Button(65440,1),new Button(65790,2),new Button(66110,3),new Button(66450,4),new Button(66790,3),new Button(67070,2),new Button(67460,1),new Button(67740,2),new Button(68090,3),new Button(68400,4),new Button(68730,3),new Button(69060,2),new Button(69370,1),new Button(69780,2),new Button(70080,3),new Button(70330,4),new Button(71510,3),new Button(71920,1),new Button(72230,2),new Button(72590,3),new Button(72760,3),new Button(72970,3),new Button(73300,4),new Button(73680,3),new Button(73870,3),new Button(74050,3),new Button(74290,2),new Button(74620,3),new Button(75300,4),new Button(75460,4),new Button(75660,4),new Button(76010,3),new Button(76390,2),new Button(76740,3),new Button(77060,2),new Button(77180,2),new Button(77250,3),new Button(77380,3),new Button(77620,3),new Button(78010,2),new Button(78260,2),new Button(78400,3),new Button(78780,2),new Button(78800,3),new Button(79140,3),new Button(79150,2),new Button(79730,3),new Button(80100,3),new Button(80490,3),new Button(80790,2),new Button(80960,2),new Button(81130,2),new Button(81470,3),new Button(81830,3),new Button(82170,3),new Button(82490,2),new Button(82670,1),new Button(82840,1),new Button(83630,2),new Button(83790,2),new Button(84140,3),new Button(84490,3),new Button(84650,3),new Button(84840,4),new Button(85030,3),new Button(85170,2),new Button(85180,1),new Button(85360,1),new Button(85560,2),new Button(85770,3),new Button(86240,3),new Button(86420,3),new Button(86590,3),new Button(86760,3),new Button(86940,2),new Button(87280,3),new Button(87600,3),new Button(87940,4),new Button(88110,4),new Button(88280,4),new Button(88430,2),new Button(88850,1),new Button(89050,1),new Button(89210,1),new Button(89530,3),new Button(89890,3),new Button(90130,2),new Button(90250,2),new Button(90450,3),new Button(90740,4),new Button(91070,3),new Button(91360,3),new Button(91480,3),new Button(91590,3),new Button(91820,2),new Button(91950,2),new Button(92070,2),new Button(92330,3),new Button(92540,3),new Button(92710,3),new Button(92890,3),new Button(93070,2),new Button(93230,2),new Button(93430,3),new Button(93610,3),new Button(93780,3),new Button(93950,3),new Button(94140,2),new Button(94400,2),new Button(94600,1),new Button(94780,1),new Button(94960,1),new Button(95160,2),new Button(95380,3),new Button(95710,4),new Button(95980,3),new Button(96180,3),new Button(96360,3),new Button(96610,2),new Button(96820,2),new Button(97130,3),new Button(97470,2),new Button(97840,3),new Button(98190,2),new Button(98500,3),new Button(98770,2),new Button(99230,3),new Button(99480,2),new Button(99770,2),new Button(100130,3),new Button(100500,3),new Button(100780,2),new Button(101150,3),new Button(101490,2),new Button(101840,3),new Button(102160,2),new Button(102480,3),new Button(102810,2),new Button(103140,3),new Button(103320,3),new Button(103520,3),new Button(103690,3),new Button(103860,3),new Button(104080,3),new Button(104250,3),new Button(104450,3),new Button(104630,3),new Button(104790,3),new Button(104960,3),new Button(105160,3),new Button(105320,3),new Button(105480,3),new Button(105730,3),new Button(105890,3),new Button(106050,3),new Button(106220,3),new Button(106390,3),new Button(106570,3),new Button(106720,3),new Button(106900,3),new Button(107070,3),new Button(107240,3),new Button(107400,3),new Button(107560,3),new Button(107720,3),new Button(107910,3),new Button(108080,3),new Button(108240,3),new Button(108430,3),new Button(108600,3),new Button(108760,3),new Button(108920,3),new Button(109100,3),new Button(109270,3),new Button(109450,3),new Button(109610,3),new Button(109760,3),new Button(109970,3),new Button(110120,3),new Button(110290,3),new Button(110450,3),new Button(110630,3),new Button(110810,3),new Button(110970,3),new Button(111130,3),new Button(111350,3),new Button(111520,3),new Button(111670,3),new Button(111930,3),new Button(112070,3),new Button(112210,3),new Button(112350,3),new Button(112650,3),new Button(113220,1),new Button(114590,4),new Button(115940,1),new Button(116650,4),new Button(117340,1),new Button(117990,4),new Button(118390,1),new Button(118630,4),new Button(118790,4),new Button(119660,1),new Button(119840,1),new Button(120030,1),new Button(121070,4),new Button(121230,4),new Button(121400,4),new Button(121710,4),new Button(121960,4),new Button(122110,4),new Button(122350,4),new Button(122520,4),new Button(122680,4),new Button(122850,4),new Button(123090,4),new Button(123530,1),new Button(123890,4),new Button(124240,1),new Button(124630,4),new Button(124990,1),new Button(125330,4),new Button(125660,1),new Button(126020,4),new Button(126330,1),new Button(126680,4),new Button(127020,1),new Button(127380,4),new Button(127740,1),new Button(128030,4),new Button(128350,1),new Button(128710,4),new Button(129020,1),new Button(129370,4),new Button(129740,1),new Button(130100,4),new Button(130420,1),new Button(130750,4),new Button(131130,1),new Button(131440,4),new Button(131790,1),new Button(132100,4),new Button(132360,1),new Button(132580,4),new Button(132780,1),new Button(132800,4),new Button(133020,4),new Button(133030,1),new Button(133150,1),new Button(133230,4),new Button(133320,1),new Button(133420,4),new Button(133490,1),new Button(133590,4),new Button(133680,1),new Button(133780,4),new Button(133830,1),new Button(134500,3),new Button(134710,3),new Button(134870,3),new Button(135120,2),new Button(135480,3),new Button(135830,2),new Button(136140,3),new Button(136400,2),new Button(136550,3),new Button(136750,3),new Button(137210,2),new Button(137390,2),new Button(137420,3),new Button(137570,3),new Button(137810,3),new Button(137990,3),new Button(138200,2),new Button(138370,3),new Button(138550,3),new Button(138740,3),new Button(138920,2),new Button(139150,3),new Button(139300,3),new Button(139450,3),new Button(139900,2),new Button(140050,2),new Button(140070,3),new Button(140260,3),new Button(140440,3),new Button(140620,3),new Button(140960,2),new Button(141130,3),new Button(141300,3),new Button(141470,3),new Button(141660,2),new Button(141860,3),new Button(142020,3),new Button(142500,2),new Button(142680,3),new Button(142850,3),new Button(143000,3),new Button(143320,3),new Button(143610,3),new Button(143780,3),new Button(143930,2),new Button(144130,3),new Button(144300,3),new Button(144440,3),new Button(144620,2),new Button(144820,3),new Button(145010,3),new Button(145190,3),new Button(145360,3),new Button(145410,2),new Button(145580,3),new Button(145590,2),new Button(145750,2),new Button(146020,3),new Button(146360,3),new Button(146710,3),new Button(147050,2),new Button(147210,2),new Button(147380,3),new Button(147550,3),new Button(147990,2),new Button(148160,2),new Button(148320,2),new Button(148470,3),new Button(148680,3),new Button(148910,3),new Button(149100,3),new Button(149250,2),new Button(149430,3),new Button(149630,2),new Button(149790,3),new Button(149870,2),new Button(150080,2),new Button(150200,3),new Button(150330,2),new Button(150530,3),new Button(150620,2),new Button(150820,3),new Button(150970,2),new Button(151110,3),new Button(151230,2),new Button(151480,3),new Button(151660,2),new Button(151800,3),new Button(152060,2),new Button(152210,3),new Button(152500,2),new Button(152560,3),new Button(152840,2),new Button(152930,3),new Button(153150,2),new Button(153450,2),new Button(153570,3),new Button(153770,2),new Button(153990,3),new Button(154210,3),new Button(154390,3),new Button(154580,3),new Button(154680,2),new Button(154840,3),new Button(154950,2),new Button(155040,3),new Button(155160,3),new Button(155340,3),new Button(155540,2),new Button(155750,3),new Button(155910,3),new Button(156090,3),new Button(156260,3),new Button(156430,2),new Button(156590,2),new Button(156690,3),new Button(156900,1),new Button(157230,4),new Button(157610,1),new Button(157950,4),new Button(158270,1),new Button(158610,4),new Button(158960,1),new Button(159320,4),new Button(159650,1),new Button(159980,4),new Button(160320,1),new Button(160640,4),new Button(160990,1),new Button(161310,4),new Button(161660,1),new Button(162020,4),new Button(162360,1),new Button(162700,4),new Button(163050,1),new Button(163380,4),new Button(163720,1),new Button(164060,4),new Button(164400,1),new Button(164740,4),new Button(165100,1),new Button(165410,4),new Button(165750,1),new Button(166080,4),new Button(166420,1),new Button(166760,4),new Button(167090,1),new Button(167430,4),new Button(167760,1),new Button(168110,1),new Button(168430,4),new Button(168790,4),new Button(169080,2),new Button(169460,3),new Button(169810,4),new Button(170150,1),new Button(170540,4),new Button(170860,4),new Button(171160,1),new Button(171500,2),new Button(171850,3),new Button(172170,4),new Button(172490,1),new Button(172880,4),new Button(173200,1),new Button(173580,4),new Button(173890,2),new Button(174240,3),new Button(174550,4),new Button(174860,1),new Button(175260,4),new Button(175570,1),new Button(175940,4),new Button(176230,2),new Button(176600,3),new Button(176930,4),new Button(177260,1),new Button(177610,4),new Button(177930,1),new Button(178230,2),new Button(178560,3),new Button(178920,4),new Button(178990,1)}),
        };

        int songCount = 3;
        Song selectedSong;
        int selectedSongIndex = 0;

    public:
        SongManager() {
            this->selectedSong = this->songs[0];
        }

        void drawSong(uint16_t x, uint16_t y, int index) {
            EADK::Display::drawString(x, y, 2, getSong(index).getName(), Black, index == this->selectedSongIndex ? LightBlue : White, 1, 2, false);
        }

        // draw selected the one before and the one after
        void drawSongList() {
            this->drawSong(20, EADK::Screen::Height / 2 - 20, this->selectedSongIndex - 1);
            this->drawSong(20, EADK::Screen::Height / 2 + 0, this->selectedSongIndex);
            this->drawSong(20, EADK::Screen::Height / 2 + 20, this->selectedSongIndex + 1);
        }

        int getSongCount() { return this->songCount; }
        Song getSelectedSong() { return this->selectedSong; }
        int getSelectedSongIndex() { return this->selectedSongIndex; }

        void setSelectedSong(int index) {
            if (index < 0) {
                index = this->songCount - 1;
            } else if (index >= this->songCount) {
                index = 0;
            }
            this->selectedSongIndex = index;
            this->selectedSong = this->songs[index];
        }
        Song getSong(int index) {
            if (index < 0) {
                index = this->songCount - 1;
            } else if (index >= this->songCount) {
                index = 0;
            }
            return this->songs[index];
        }
};

} // namespace songs
} // namespace platform

#endif
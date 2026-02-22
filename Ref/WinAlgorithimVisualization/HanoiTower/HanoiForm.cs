using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace HanoiTower
{
    public sealed class HanoiForm : Form
    {
        // ----- UI -----
        private readonly NumericUpDown nudDisks = new() { Minimum = 1, Maximum = 12, Value = 5, Width = 60 };
        private readonly Button btnStart = new() { Text = "Start", Width = 80 };
        private readonly Button btnReset = new() { Text = "Reset", Width = 80 };
        private readonly TrackBar tbSpeed = new() { Minimum = 1, Maximum = 30, Value = 10, TickStyle = TickStyle.None, Width = 140 };
        private readonly Label lblInfo = new() { AutoSize = true, Text = "Moves: 0 / 0" };

        // ----- Animation -----
        private readonly System.Windows.Forms.Timer timer = new();
        private List<Move> moves = new();
        private int moveIndex = 0;

        // ----- State (3 pegs) -----
        // 각 스택: 맨 위 원반이 Stack의 Top (Pop/Push)
        private readonly Stack<int>[] pegs = { new Stack<int>(), new Stack<int>(), new Stack<int>() };

        // ----- Rendering settings -----
        private const int PegCount = 3;
        private const int PegWidth = 10;
        private const int PegTopMargin = 60;
        private const int PegBottomMargin = 50;
        private const int DiskHeight = 18;
        private const int DiskMinWidth = 40;
        private const int DiskWidthStep = 18;

        public HanoiForm()
        {
            Text = "Hanoi Tower Visualizer (WinForms)";
            DoubleBuffered = true;
            ClientSize = new Size(900, 600);

            // Top panel
            var panel = new FlowLayoutPanel
            {
                Dock = DockStyle.Top,
                Height = 48,
                Padding = new Padding(12, 10, 12, 8),
                FlowDirection = FlowDirection.LeftToRight,
                WrapContents = false
            };

            panel.Controls.Add(new Label { AutoSize = true, Text = "Disks:", Padding = new Padding(0, 6, 6, 0) });
            panel.Controls.Add(nudDisks);

            panel.Controls.Add(new Label { AutoSize = true, Text = "   Speed:", Padding = new Padding(12, 6, 6, 0) });
            panel.Controls.Add(tbSpeed);

            panel.Controls.Add(new Label { AutoSize = true, Text = "   ", Padding = new Padding(6, 0, 6, 0) });
            panel.Controls.Add(btnStart);
            panel.Controls.Add(btnReset);

            panel.Controls.Add(new Label { AutoSize = true, Text = "   ", Padding = new Padding(6, 0, 6, 0) });
            panel.Controls.Add(lblInfo);

            Controls.Add(panel);

            // Timer
            timer.Interval = SpeedToInterval(tbSpeed.Value);
            timer.Tick += (_, __) => Step();

            // Events
            tbSpeed.ValueChanged += (_, __) => timer.Interval = SpeedToInterval(tbSpeed.Value);
            btnStart.Click += (_, __) => StartRun();
            btnReset.Click += (_, __) => ResetState((int)nudDisks.Value);

            // init
            ResetState((int)nudDisks.Value);
        }

        private static int SpeedToInterval(int speed)
        {
            // speed 1..30 => interval 800..40 ms 정도로 변환
            // speed가 높을수록 빠르게
            int interval = 800 - (speed - 1) * 26;
            return Math.Max(40, interval);
        }

        // -------- Hanoi Logic: move list 만들기 --------
        private static void BuildMoves(List<Move> list, int no, int from, int to)
        {
            if (no <= 0) return;

            int aux = 3 - from - to; // 0,1,2 사용 (합 0+1+2=3)
            if (no > 1)
                BuildMoves(list, no - 1, from, aux);

            list.Add(new Move(no, from, to));

            if (no > 1)
                BuildMoves(list, no - 1, aux, to);
        }

        // -------- Run Control --------
        private void StartRun()
        {
            if (timer.Enabled)
            {
                timer.Stop();
                btnStart.Text = "Start";
                return;
            }

            // 새 실행이면 초기화
            if (moveIndex == 0 && moves.Count == 0)
            {
                int n = (int)nudDisks.Value;
                ResetState(n);

                moves = new List<Move>(capacity: (1 << n) - 1);
                BuildMoves(moves, n, 0, 2);
                UpdateInfo();
            }

            timer.Start();
            btnStart.Text = "Pause";
        }

        private void Step()
        {
            if (moveIndex >= moves.Count)
            {
                timer.Stop();
                btnStart.Text = "Start";
                return;
            }

            var m = moves[moveIndex];

            // 스택 기반 상태 업데이트
            // from peg에서 Pop -> to peg에 Push
            if (pegs[m.From].Count == 0)
            {
                timer.Stop();
                MessageBox.Show("Invalid state: source peg empty");
                btnStart.Text = "Start";
                return;
            }

            int disk = pegs[m.From].Pop();

            if (disk != m.Disk)
            {
                // 디버그/안전: 알고리즘과 상태 불일치
                timer.Stop();
                MessageBox.Show($"Invalid move: expected disk {m.Disk} but got {disk}");
                btnStart.Text = "Start";
                return;
            }

            if (pegs[m.To].Count > 0 && pegs[m.To].Peek() < disk)
            {
                timer.Stop();
                MessageBox.Show("Invalid move: larger disk on smaller disk");
                btnStart.Text = "Start";
                return;
            }

            pegs[m.To].Push(disk);

            moveIndex++;
            UpdateInfo();
            Invalidate(); // repaint
        }

        private void ResetState(int n)
        {
            timer.Stop();
            btnStart.Text = "Start";

            moves.Clear();
            moveIndex = 0;

            foreach (var s in pegs) s.Clear();

            // peg 0에 큰 원반부터 쌓기 (바닥: n, 맨 위: 1)
            for (int d = n; d >= 1; d--)
                pegs[0].Push(d);

            UpdateInfo();
            Invalidate();
        }

        private void UpdateInfo()
        {
            lblInfo.Text = $"Moves: {moveIndex} / {moves.Count}";
        }

        // -------- Rendering --------
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            int w = ClientSize.Width;
            int h = ClientSize.Height;

            int baseY = h - PegBottomMargin;
            int pegTopY = PegTopMargin;
            int pegHeight = baseY - pegTopY;

            // peg x positions
            int[] pegX = new int[PegCount];
            for (int i = 0; i < PegCount; i++)
                pegX[i] = (int)((i + 0.5) * w / PegCount);

            // draw base line
            using (var basePen = new Pen(Color.DimGray, 4))
                g.DrawLine(basePen, 40, baseY, w - 40, baseY);

            // draw pegs
            using (var pegBrush = new SolidBrush(Color.Gray))
            {
                for (int i = 0; i < PegCount; i++)
                {
                    var rect = new Rectangle(pegX[i] - PegWidth / 2, pegTopY, PegWidth, pegHeight);
                    g.FillRectangle(pegBrush, rect);

                    // peg label
                    using var f = new Font(Font.FontFamily, 11, FontStyle.Bold);
                    var s = $"Peg {i + 1}";
                    var size = g.MeasureString(s, f);
                    g.DrawString(s, f, Brushes.Black, pegX[i] - size.Width / 2, baseY + 8);
                }
            }

            // draw disks (각 peg의 스택을 아래에서 위로 그려야 함)
            int maxDisk = (int)nudDisks.Value;

            for (int i = 0; i < PegCount; i++)
            {
                int[] disks = pegs[i].ToArray();      // top->bottom
                Array.Reverse(disks);                 // bottom->top

                for (int level = 0; level < disks.Length; level++)
                {
                    int d = disks[level];
                    int diskW = DiskMinWidth + (d - 1) * DiskWidthStep;

                    int x = pegX[i] - diskW / 2;
                    int y = baseY - DiskHeight * (level + 1);

                    // 색: 디스크 번호 기반으로 적당히 변화 (고정 팔레트)
                    Color c = DiskColor(d, maxDisk);

                    using var b = new SolidBrush(c);
                    using var p = new Pen(Color.Black, 1);

                    var r = new Rectangle(x, y, diskW, DiskHeight - 2);
                    g.FillRoundedRectangle(b, r, 10);
                    g.DrawRoundedRectangle(p, r, 10);

                    // disk label
                    using var f = new Font(Font.FontFamily, 9, FontStyle.Bold);
                    string label = d.ToString();
                    var size = g.MeasureString(label, f);
                    g.DrawString(label, f, Brushes.White,
                        x + diskW / 2 - size.Width / 2,
                        y + (DiskHeight - size.Height) / 2 - 1);
                }
            }
        }

        private static Color DiskColor(int disk, int maxDisk)
        {
            // disk 1..maxDisk → 색상 분포
            // HSV 같은 거 쓰지 않고 간단히 RGB로 변형
            double t = (maxDisk <= 1) ? 0 : (double)(disk - 1) / (maxDisk - 1);
            int r = (int)(60 + 140 * (1 - t));
            int g = (int)(80 + 140 * (t));
            int b = (int)(180 - 80 * t);
            return Color.FromArgb(r, g, b);
        }

        // ----- Move record -----
        private readonly record struct Move(int Disk, int From, int To);
    }

    internal static class GraphicsExtensions
    {
        public static void FillRoundedRectangle(this Graphics g, Brush brush, Rectangle r, int radius)
        {
            using var path = RoundedRectPath(r, radius);
            g.FillPath(brush, path);
        }

        public static void DrawRoundedRectangle(this Graphics g, Pen pen, Rectangle r, int radius)
        {
            using var path = RoundedRectPath(r, radius);
            g.DrawPath(pen, path);
        }

        private static System.Drawing.Drawing2D.GraphicsPath RoundedRectPath(Rectangle r, int radius)
        {
            int d = radius * 2;
            var path = new System.Drawing.Drawing2D.GraphicsPath();
            path.AddArc(r.Left, r.Top, d, d, 180, 90);
            path.AddArc(r.Right - d, r.Top, d, d, 270, 90);
            path.AddArc(r.Right - d, r.Bottom - d, d, d, 0, 90);
            path.AddArc(r.Left, r.Bottom - d, d, d, 90, 90);
            path.CloseFigure();
            return path;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace EightQueen
{
    public sealed class QueensForm : Form
    {
        // ===== UI =====
        private readonly Button btnStart = new() { Text = "Start", Width = 90 };
        private readonly Button btnReset = new() { Text = "Reset", Width = 90 };
        private readonly Button btnShowSolution = new() { Text = "Show solution", Width = 120 };
        private readonly NumericUpDown nudSolution = new() { Minimum = 1, Maximum = 92, Value = 1, Width = 60 };
        private readonly TrackBar tbSpeed = new() { Minimum = 1, Maximum = 30, Value = 12, TickStyle = TickStyle.None, Width = 160 };
        private readonly Label lblInfo = new() { AutoSize = true, Text = "Ready" };

        private readonly System.Windows.Forms.Timer timer = new();

        // ===== Board/State =====
        private const int N = 8;

        // current board for animation:
        // col -> row (0..7), -1 means not placed
        private readonly int[] colToRow = Enumerable.Repeat(-1, N).ToArray();

        // for solution viewing:
        private List<int[]> solutions = new();

        // ===== Backtracking optimization sets (for animation) =====
        private readonly bool[] usedRow = new bool[N];
        private readonly bool[] usedDiag1 = new bool[2 * N - 1]; // r - c + 7
        private readonly bool[] usedDiag2 = new bool[2 * N - 1]; // r + c

        // ===== Animation plan (steps) =====
        private readonly List<Step> steps = new();
        private int stepIndex = 0;
        private bool isAnimating = false;
        private bool showFixedSolution = false;

        // ===== Rendering =====
        private readonly Font fontCell = new Font("Segoe UI", 11, FontStyle.Bold);
        private readonly Font fontQueen = new Font("Segoe UI Symbol", 22, FontStyle.Bold);

        public QueensForm()
        {
            Text = "8-Queens Visualizer (WinForms)";
            DoubleBuffered = true;
            ClientSize = new Size(900, 650);

            // Top controls
            var panel = new FlowLayoutPanel
            {
                Dock = DockStyle.Top,
                Height = 52,
                Padding = new Padding(12, 10, 12, 8),
                FlowDirection = FlowDirection.LeftToRight,
                WrapContents = false
            };

            panel.Controls.Add(btnStart);
            panel.Controls.Add(btnReset);

            panel.Controls.Add(new Label { AutoSize = true, Text = "   Speed:", Padding = new Padding(10, 6, 6, 0) });
            panel.Controls.Add(tbSpeed);

            panel.Controls.Add(new Label { AutoSize = true, Text = "   Solution #:", Padding = new Padding(12, 6, 6, 0) });
            panel.Controls.Add(nudSolution);
            panel.Controls.Add(btnShowSolution);

            panel.Controls.Add(new Label { AutoSize = true, Text = "   ", Padding = new Padding(10, 0, 10, 0) });
            panel.Controls.Add(lblInfo);

            Controls.Add(panel);

            // Timer
            timer.Interval = SpeedToInterval(tbSpeed.Value);
            timer.Tick += (_, __) => TickStep();

            tbSpeed.ValueChanged += (_, __) => timer.Interval = SpeedToInterval(tbSpeed.Value);

            btnStart.Click += (_, __) =>
            {
                if (!isAnimating) StartAnimation();
                else TogglePause();
            };

            btnReset.Click += (_, __) => ResetAll();

            btnShowSolution.Click += (_, __) => ShowSolution((int)nudSolution.Value);

            // Precompute solutions + steps (fast)
            BuildAllSolutions();
            nudSolution.Maximum = solutions.Count;
            lblInfo.Text = $"Solutions: {solutions.Count} (expected 92)";

            ResetAll();
        }

        private static int SpeedToInterval(int speed)
        {
            // 1..30 => 900..30ms
            int interval = 900 - (speed - 1) * 30;
            return Math.Max(30, interval);
        }

        // =========================
        // Build solutions (backtracking)
        // =========================
        private void BuildAllSolutions()
        {
            solutions.Clear();
            Array.Fill(colToRow, -1);

            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);

            void Dfs(int col)
            {
                if (col == N)
                {
                    solutions.Add((int[])colToRow.Clone());
                    return;
                }

                for (int row = 0; row < N; row++)
                {
                    if (!CanPlace(row, col)) continue;

                    Place(row, col);
                    Dfs(col + 1);
                    Remove(row, col);
                }
            }

            Dfs(0);

            // restore empty
            Array.Fill(colToRow, -1);
            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);
        }

        // =========================
        // Build animation steps (place/remove attempts)
        // =========================
        private void BuildStepsForAnimation()
        {
            steps.Clear();
            stepIndex = 0;

            Array.Fill(colToRow, -1);
            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);

            void Dfs(int col)
            {
                if (col == N)
                {
                    // found one solution
                    steps.Add(Step.FoundSolution());
                    return;
                }

                for (int row = 0; row < N; row++)
                {
                    // record attempt (optional highlight)
                    steps.Add(Step.Try(row, col));

                    if (!CanPlace(row, col))
                    {
                        steps.Add(Step.Reject(row, col));
                        continue;
                    }

                    // place
                    Place(row, col);
                    steps.Add(Step.Place(row, col));

                    Dfs(col + 1);

                    // remove
                    Remove(row, col);
                    steps.Add(Step.Remove(row, col));
                }
            }

            Dfs(0);

            // leave state empty at end
            Array.Fill(colToRow, -1);
            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);
        }

        private bool CanPlace(int row, int col)
        {
            int d1 = row - col + (N - 1);
            int d2 = row + col;
            return !usedRow[row] && !usedDiag1[d1] && !usedDiag2[d2];
        }

        private void Place(int row, int col)
        {
            colToRow[col] = row;
            usedRow[row] = true;
            usedDiag1[row - col + (N - 1)] = true;
            usedDiag2[row + col] = true;
        }

        private void Remove(int row, int col)
        {
            colToRow[col] = -1;
            usedRow[row] = false;
            usedDiag1[row - col + (N - 1)] = false;
            usedDiag2[row + col] = false;
        }

        // =========================
        // Controls
        // =========================
        private void ResetAll()
        {
            timer.Stop();
            isAnimating = false;
            showFixedSolution = false;
            btnStart.Text = "Start";

            Array.Fill(colToRow, -1);
            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);

            steps.Clear();
            stepIndex = 0;

            lblInfo.Text = $"Ready. Solutions: {solutions.Count}";
            Invalidate();
        }

        private void StartAnimation()
        {
            showFixedSolution = false;

            if (steps.Count == 0)
                BuildStepsForAnimation();

            // reset state for animation playback
            Array.Fill(colToRow, -1);
            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);

            stepIndex = 0;
            isAnimating = true;
            btnStart.Text = "Pause";
            timer.Start();
        }

        private void TogglePause()
        {
            if (!isAnimating) return;

            if (timer.Enabled)
            {
                timer.Stop();
                btnStart.Text = "Resume";
            }
            else
            {
                timer.Start();
                btnStart.Text = "Pause";
            }
        }

        private void ShowSolution(int k)
        {
            timer.Stop();
            isAnimating = false;
            btnStart.Text = "Start";
            showFixedSolution = true;

            int idx = Math.Clamp(k - 1, 0, solutions.Count - 1);
            var sol = solutions[idx];

            // rebuild board state from solution
            Array.Fill(colToRow, -1);
            Array.Clear(usedRow, 0, usedRow.Length);
            Array.Clear(usedDiag1, 0, usedDiag1.Length);
            Array.Clear(usedDiag2, 0, usedDiag2.Length);

            for (int col = 0; col < N; col++)
            {
                int row = sol[col];
                Place(row, col);
            }

            lblInfo.Text = $"Showing solution #{idx + 1} / {solutions.Count}";
            Invalidate();
        }

        // =========================
        // Animation tick
        // =========================
        private Step lastStep = default;

        private void TickStep()
        {
            if (!isAnimating)
            {
                timer.Stop();
                return;
            }

            if (stepIndex >= steps.Count)
            {
                timer.Stop();
                isAnimating = false;
                btnStart.Text = "Start";
                lblInfo.Text = $"Done. Solutions: {solutions.Count}";
                lastStep = default;
                Invalidate();
                return;
            }

            var s = steps[stepIndex++];
            lastStep = s;

            switch (s.Kind)
            {
                case StepKind.Place:
                    if (CanPlace(s.Row, s.Col))
                        Place(s.Row, s.Col);
                    break;

                case StepKind.Remove:
                    // remove must match current placement
                    if (colToRow[s.Col] == s.Row)
                        Remove(s.Row, s.Col);
                    break;

                case StepKind.FoundSolution:
                    timer.Stop();
                    btnStart.Text = "Resume";
                    lblInfo.Text += "  (Solution found - paused)";
                    return;

                // Try/Reject are only for highlighting/labels
                case StepKind.Try:
                case StepKind.Reject:
                    break;
            }

            int foundSoFar = steps.Take(stepIndex).Count(x => x.Kind == StepKind.FoundSolution);
            lblInfo.Text = $"Animating... step {stepIndex}/{steps.Count}, found {foundSoFar}/{solutions.Count}";
            Invalidate();
        }

        // =========================
        // Painting
        // =========================
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            var g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            var boardRect = GetBoardRect();
            DrawBoard(g, boardRect);
            DrawQueens(g, boardRect);
            DrawOverlay(g, boardRect);
        }

        private Rectangle GetBoardRect()
        {
            int top = 70;
            int padding = 30;
            int size = Math.Min(ClientSize.Width - padding * 2, ClientSize.Height - top - 40);
            int x = (ClientSize.Width - size) / 2;
            int y = top + (ClientSize.Height - top - size) / 2;
            return new Rectangle(x, y, size, size);
        }

        private void DrawBoard(Graphics g, Rectangle r)
        {
            int cell = r.Width / N;

            using var light = new SolidBrush(Color.FromArgb(240, 240, 240));
            using var dark = new SolidBrush(Color.FromArgb(180, 180, 180));
            using var borderPen = new Pen(Color.Black, 2);

            for (int row = 0; row < N; row++)
            {
                for (int col = 0; col < N; col++)
                {
                    bool isDark = ((row + col) % 2 == 1);
                    var cellRect = new Rectangle(r.X + col * cell, r.Y + row * cell, cell, cell);
                    g.FillRectangle(isDark ? dark : light, cellRect);
                }
            }

            g.DrawRectangle(borderPen, r);

            // coordinate hints (optional)
            for (int i = 0; i < N; i++)
            {
                string s = i.ToString();
                var size = g.MeasureString(s, fontCell);

                // top labels (col)
                g.DrawString(s, fontCell, Brushes.Black,
                    r.X + i * cell + cell / 2 - size.Width / 2,
                    r.Y - size.Height - 4);

                // left labels (row)
                g.DrawString(s, fontCell, Brushes.Black,
                    r.X - size.Width - 8,
                    r.Y + i * cell + cell / 2 - size.Height / 2);
            }
        }

        private void DrawQueens(Graphics g, Rectangle r)
        {
            int cell = r.Width / N;

            for (int col = 0; col < N; col++)
            {
                int row = colToRow[col];
                if (row < 0) continue;

                var cellRect = new Rectangle(r.X + col * cell, r.Y + row * cell, cell, cell);

                // draw queen symbol
                string q = "♛";
                var size = g.MeasureString(q, fontQueen);
                float x = cellRect.X + cell / 2f - size.Width / 2f;
                float y = cellRect.Y + cell / 2f - size.Height / 2f;

                // shadow
                g.DrawString(q, fontQueen, Brushes.Black, x + 1.5f, y + 1.5f);
                // main
                g.DrawString(q, fontQueen, Brushes.Gold, x, y);
            }
        }

        private void DrawOverlay(Graphics g, Rectangle boardRect)
        {
            // highlight last attempted cell
            if (showFixedSolution) return; // no overlay in fixed solution mode
            if (!isAnimating) return;
            if (lastStep.Kind is not (StepKind.Try or StepKind.Reject or StepKind.Place)) return;

            int cell = boardRect.Width / N;
            var cellRect = new Rectangle(
                boardRect.X + lastStep.Col * cell,
                boardRect.Y + lastStep.Row * cell,
                cell,
                cell);

            using var pen = new Pen(lastStep.Kind == StepKind.Reject ? Color.Red : Color.DeepSkyBlue, 3);
            g.DrawRectangle(pen, cellRect);

            if (lastStep.Kind == StepKind.Reject)
            {
                using var xPen = new Pen(Color.Red, 3);
                g.DrawLine(xPen, cellRect.Left + 6, cellRect.Top + 6, cellRect.Right - 6, cellRect.Bottom - 6);
                g.DrawLine(xPen, cellRect.Right - 6, cellRect.Top + 6, cellRect.Left + 6, cellRect.Bottom - 6);
            }
        }

        // =========================
        // Step model
        // =========================
        private enum StepKind { Try, Reject, Place, Remove, FoundSolution }

        private readonly record struct Step(StepKind Kind, int Row, int Col)
        {
            public static Step Try(int row, int col) => new(StepKind.Try, row, col);
            public static Step Reject(int row, int col) => new(StepKind.Reject, row, col);
            public static Step Place(int row, int col) => new(StepKind.Place, row, col);
            public static Step Remove(int row, int col) => new(StepKind.Remove, row, col);
            public static Step FoundSolution() => new(StepKind.FoundSolution, -1, -1);
        }
    }
}

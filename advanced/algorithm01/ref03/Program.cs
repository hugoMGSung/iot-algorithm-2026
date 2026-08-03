namespace ref03 {
    internal class Program {
        static void Main(string[] args) {
            Dictionary<string, int> studentScore = new();

            studentScore["Alice"] = 95;
            studentScore["Bob"] = 88;
            studentScore["Charlie"] = 92;
            studentScore["Rabbit"] = 0;

            foreach (var score in studentScore) {
                System.Console.WriteLine(score);
            }

            int score2 = studentScore["Rabbit"];
            Console.WriteLine(score2);
        }
    }
}

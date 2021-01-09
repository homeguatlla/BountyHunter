#pragma once
#include "IGoal.h"

#include <vector>
#include <memory>
#include <map>

namespace NAI
{
	namespace Goap
	{
		class IAction;

		class BaseGoal : public IGoal, public std::enable_shared_from_this<BaseGoal>
		{
		public:
			BaseGoal();
			BaseGoal(const std::vector<std::shared_ptr<IAction>>& actions);
			virtual ~BaseGoal() = default;

			void Create(std::shared_ptr<IAgent> agent) override;
			std::shared_ptr<IAction> GetNextAction() override;
			bool HasActions() const override { return mCurrentActionIndex < mActions.size(); }
			unsigned int GetCost() const override { return mCost; }
			unsigned int GetCost(std::vector<std::shared_ptr<IPredicate>>& inputPredicates) const override { return mCost; }
			bool SatisfyActions(const std::vector<std::shared_ptr<IPredicate>>& inputPredicates) override;
			void Accomplished(std::vector<std::shared_ptr<IPredicate>>& predicates) final override;
			void Cancel() final override;
			void Reset() final override;
			std::vector<std::shared_ptr<IPredicate>> GetPredicatesCanBeAccomplished(std::vector<std::shared_ptr<IPredicate>> desiredPredicates) override;
			std::vector<std::shared_ptr<IPredicate>> GetPredicatesSatisfyPreconditions(std::vector<std::shared_ptr<IPredicate>> inputPredicates) override;

			void AddStimulusAcceptance(const std::string& stimulusClassName, std::function<std::shared_ptr<IPredicate>(std::shared_ptr<IStimulus>)> creator) override;
			bool IsStimulusAccepted(std::shared_ptr<IStimulus> stimulus) const override;
			std::shared_ptr<IPredicate>	TransformStimulusIntoPredicates(std::shared_ptr<IStimulus> stimulus) const override;
		
		protected:
			virtual void DoCreate(const std::shared_ptr<IAgent>& agent) {}
			virtual void DoAccomplished(std::vector<std::shared_ptr<IPredicate>>& predicates) {}
			virtual void DoCancel() {}
			virtual void DoReset() {}
			virtual std::shared_ptr<IPredicate> DoAccept(std::shared_ptr<IStimulus> stimulus) const { return {}; }

		private:
			void CalculateCost();

		protected:
			std::vector<std::shared_ptr<IAction>> mActions;
			std::map<std::string, std::function<std::shared_ptr<IPredicate>(std::shared_ptr<IStimulus>)>> mStimulusAccepted;
			unsigned int mCurrentActionIndex;
			unsigned int mCost;
		};
	}
}

